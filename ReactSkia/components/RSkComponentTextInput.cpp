/*
 * Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/core/SkPaint.h"
#include "ReactSkia/components/RSkComponentTextInput.h"
#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/sdk/RNSKeyCodeMapping.h"
#include "ReactSkia/views/common/RSkDrawUtils.h"
#include "ReactSkia/views/common/RSkConversion.h"
#include "rns_shell/compositor/layers/PictureLayer.h"

#include <string.h>
#include <iostream>
#include <queue>
#include <thread>
#include <semaphore.h>
#include <mutex>  
std::mutex mtx;

namespace facebook {
namespace react {

using namespace RSkDrawUtils;
using namespace skia::textlayout;

#define NUMBER_OF_LINES         1
#define FONTSIZE_MULTIPLIER     10
#define CURSOR_WIDTH 2
std::queue<rnsKey> inputQueue;
sem_t mutex;

RSkComponentTextInput::RSkComponentTextInput(const ShadowView &shadowView)
    : RSkComponent(shadowView)
    ,isInEditingMode_(false)
    ,eventCount_(0)
    ,cursor_({0,0}){
  RNS_LOG_DEBUG("called constructor");
  paragraph_ = nullptr;
  cursorPaint_.setColor(SK_ColorBLUE);
  cursorPaint_.setAntiAlias(true);
  cursorPaint_.setStyle(SkPaint::kStroke_Style);
  cursorPaint_.setStrokeWidth(CURSOR_WIDTH);
  isThreadWantToExit_ = true;
}

void RSkComponentTextInput::flushLayer(){
  layer()->client().notifyFlushBegin();
  layer()->invalidate( RnsShell::LayerPaintInvalidate);
  if (layer()->type() == RnsShell::LAYER_TYPE_PICTURE) {
    RNS_PROFILE_API_OFF(getComponentData().componentName << " getPicture :", static_cast<RnsShell::PictureLayer*>(layer().get())->setPicture(getPicture()));
  }
  layer()->client().notifyFlushRequired();
}

void RSkComponentTextInput::drawTextInput(SkCanvas *canvas,
  LayoutMetrics layout,
  std::shared_ptr<ParagraphBuilder> &builder,
  const TextInputProps& props) {
  Rect frame = layout.frame;
  ParagraphStyle paraStyle;
  float yOffset;
  
  //cursor
  int position = 0;
  SkRect cursorRect;
  std::vector<TextBox> rects;

  // setParagraphStyle
  paraStyle.setMaxLines(NUMBER_OF_LINES);
  paraStyle.setEllipsis(u"\u2026");
  builder->setParagraphStyle(paraStyle);

  // buildParagraph
  paragraph_ = builder->Build();
  paragraph_->layout(layout.getContentFrame().size.width);

  // clipRect and backgroundColor
  canvas->clipRect(SkRect::MakeXYWH(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height));
  canvas->drawColor(RSkColorFromSharedColor(props.backgroundColor, SK_ColorTRANSPARENT));

  // paintParagraph
  yOffset = (layout.getContentFrame().size.height - paragraph_->getHeight()) / 2;
  paragraph_->paint(canvas, frame.origin.x + layout.contentInsets.left, frame.origin.y + layout.contentInsets.top + yOffset);

  // draw Cursor
  if (!caretHidden_) {
  position = cursor_.end - cursor_.locationFromEnd;
  if (cursor_.locationFromEnd == cursor_.end) {
    rects = paragraph_->getRectsForRange(0, position+1, RectHeightStyle::kTight, RectWidthStyle::kTight);
    cursorRect.fLeft =  frame.origin.x + rects[0].rect.left() + layout.contentInsets.left;
    cursorRect.fRight = cursorRect.fLeft;
  } else {
    rects = paragraph_->getRectsForRange(0, position, RectHeightStyle::kTight, RectWidthStyle::kTight);
    cursorRect.fLeft =  frame.origin.x + rects[0].rect.right() + layout.contentInsets.left;
    cursorRect.fRight = cursorRect.fLeft;
  }
  cursorRect.fTop = frame.origin.y + yOffset + layout.contentInsets.top;
  cursorRect.fBottom = cursorRect.fTop + paragraph_->getHeight();
  canvas->drawRect(cursorRect, cursorPaint_);
  }
}

void RSkComponentTextInput::OnPaint(SkCanvas *canvas) {
  auto component = getComponentData();
  auto const &textInputProps = *std::static_pointer_cast<TextInputProps const>(component.props);
  auto state = std::static_pointer_cast<TextInputShadowNode::ConcreteStateT const>(component.state);
  auto data = state->getData();
  auto borderMetrics = textInputProps.resolveBorderMetrics(component.layoutMetrics);
  Rect frame = component.layoutMetrics.frame;
  ParagraphStyle paraStyle;
  TextShadow shadow;
  TextAttributes textAttributes = textInputProps.getEffectiveTextAttributes(FONTSIZE_MULTIPLIER);
  auto paraBuilder = std::static_pointer_cast<skia::textlayout::ParagraphBuilder>(
                          std::make_shared<skia::textlayout::ParagraphBuilderImpl>(
                          paraStyle, data.layoutManager->collection_));

  if (0 == displayString_.size()) {
    textAttributes.foregroundColor = placeholderColor_;
    data.layoutManager->buildText(textInputProps.paragraphAttributes, textAttributes, placeholderString_, shadow, true, paraBuilder);
  } else {
    data.layoutManager->buildText(textInputProps.paragraphAttributes, textAttributes, displayString_, shadow, true, paraBuilder);
  }

  drawShadow(canvas, frame, borderMetrics, textInputProps.backgroundColor, layer()->shadowOpacity, layer()->shadowFilter);
  drawTextInput(canvas, component.layoutMetrics, paraBuilder, textInputProps);
  drawBorder(canvas, frame, borderMetrics, textInputProps.backgroundColor);
}

/*
* @brief       Handling the key Event in TextInput.
* @param       eventKeyType, is Key type
* @param[out]  StopPropogation set false if evnt should be progated furtuer (bubbling)
*              else true if you want to stop propogation of event
* @return      True if key is handled else false
*/

void RSkComponentTextInput::onHandleKey(rnsKey eventKeyType, bool *stopPropagation) {
  *stopPropagation = false;
  if (!editable_) {
    return;
  }
  mtx.lock();
  std::string textString = displayString_;
  KeyPressMetrics keyPressMetrics;
  TextInputMetrics textInputMetrics;
  *stopPropagation = false;
  cursor_.end = textString.length();
  mtx.unlock();
  auto component = getComponentData();
  Rect frame = component.layoutMetrics.frame;
  auto textInputEventEmitter = std::static_pointer_cast<TextInputEventEmitter const>(component.eventEmitter);
  auto const &textInputProps = *std::static_pointer_cast<TextInputProps const>(component.props);
  textInputMetrics.contentOffset.x = frame.origin.x;
  textInputMetrics.contentOffset.y = frame.origin.y;
  if (isInEditingMode_ == false && eventKeyType == RNS_KEY_Select ) {
    RNS_LOG_DEBUG("onfocus need to here"<<textInputMetrics.text);
    textInputMetrics.contentSize.width = paragraph_->getMaxIntrinsicWidth();
    textInputMetrics.contentSize.height = paragraph_->getHeight();
    textInputEventEmitter->onFocus(textInputMetrics);
    isInEditingMode_ = true;
  } else if (isInEditingMode_) {
    // Logic to update the textinput string.
    // Requirement: Textinput is in Editing mode.
    // 1. Alphanumeric keys
    // case 1: appending at end
    // case 2: insert in mid
    // Navigation Keys.
    // 2. update relative location of cursor based
    // on LEFT/RIGHT navigation keys.
    // 3. Deleting character.
    // case 1: Delete last update character by default.
    // case 2: Base on absolute location of cursor.
    // Always delete the immediate left character from
    // the cursor position.
      
    if(textInputProps.value.has_value()) {
      if(isThreadWantToExit_){
        RNS_LOG_INFO("Create Thread based on the Exit Condition");
        std::thread t(&RSkComponentTextInput::workerThread,this);
        t.detach();
        isThreadWantToExit_ = false;
      }
      mtx.lock();
      RNS_LOG_INFO("Key is pushing to Queue");
      inputQueue.push(eventKeyType);
      mtx.unlock();
      //We need to Handle the StopPrpagation & select in the onHandle.
      if ((eventKeyType >= RNS_KEY_1 && eventKeyType <= RNS_KEY_z)) {
        *stopPropagation = true;
   
      } else {
        switch(eventKeyType){
          case RNS_KEY_Left:
          case RNS_KEY_Right:
          case RNS_KEY_Back:
          case RNS_KEY_Delete:
            *stopPropagation = true;
            RNS_LOG_INFO("case Left,RIGHT,BACK,Delete");
          break;
          case RNS_KEY_Select:
            RNS_LOG_INFO(" case Select");
            *stopPropagation = true;
            isThreadWantToExit_ = true;
            isInEditingMode_ = false;
            //TODO Clear the queue
            //Don't use the Own Function
            mtx.lock();
            while (!inputQueue.empty())
            {
              RNS_LOG_INFO(" Poping Queue");
              inputQueue.pop();
            }
            mtx.unlock();
            //Use the standard API.
            eventCount_++;
            RNS_LOG_INFO(" Assigning String");
            textInputMetrics.text = textString;
            textInputMetrics.eventCount = eventCount_;
            RNS_LOG_INFO(" Sending Events");
            textInputEventEmitter->onSubmitEditing(textInputMetrics);
            textInputEventEmitter->onEndEditing(textInputMetrics);
            textInputEventEmitter->onBlur(textInputMetrics);   
            
            break;
          default:
            RNS_LOG_INFO("case Default");
            break;
        }
      }
      return;
    }

    keyPressMetrics.text = RNSKeyMap[eventKeyType];
    if ((eventKeyType >= RNS_KEY_1 && eventKeyType <= RNS_KEY_z)) {
      if (cursor_.locationFromEnd != 0){
        textString.insert(cursor_.end-cursor_.locationFromEnd,keyPressMetrics.text);
      } else {
        textString = textString+keyPressMetrics.text;
      }
    } else {
      switch(eventKeyType){
        case RNS_KEY_Left:
          if(cursor_.locationFromEnd < cursor_.end ){
            RNS_LOG_DEBUG("Right key pressed cursor_.locationFromEnd = "<<cursor_.locationFromEnd);
            cursor_.locationFromEnd++; // locationFromEnd
          }
          *stopPropagation = true;
          keyPressMetrics.eventCount = eventCount_;
          flushLayer();
          textInputEventEmitter->onKeyPress(keyPressMetrics);
          return;
        case RNS_KEY_Right:
          if (cursor_.locationFromEnd>0){
            RNS_LOG_DEBUG("Right key pressed cursor_.locationFromEnd = "<<cursor_.locationFromEnd);
            cursor_.locationFromEnd--;
          }
          *stopPropagation = true;
          keyPressMetrics.eventCount = eventCount_;
          flushLayer();
          textInputEventEmitter->onKeyPress(keyPressMetrics);
          return;
        case RNS_KEY_Back:
        case RNS_KEY_Delete:
          if (!textString.empty() && (cursor_.end!=cursor_.locationFromEnd) )
            textString.erase(textString.begin()+(cursor_.end-cursor_.locationFromEnd-1)); //acts like a backspace.
            RNS_LOG_DEBUG("After removing a charector in string = "<<textString); 
          break;
        case RNS_KEY_Select:
          eventCount_++;
          textInputMetrics.text = textString;
          textInputMetrics.eventCount = eventCount_;
          textInputEventEmitter->onSubmitEditing(textInputMetrics);
          textInputEventEmitter->onEndEditing(textInputMetrics);
          textInputEventEmitter->onBlur(textInputMetrics);
          isInEditingMode_ = false;
          *stopPropagation = true;
          return;
        default:
          return;//noop
      }
    }
    //currently selection is not supported selectionRange length is 
    //is always 0 & selectionRange.location always end 
    textInputMetrics.selectionRange.location = cursor_.end ;
    textInputMetrics.selectionRange.length = 0;
    if (displayString_ != textString){
      displayString_ = textString;
      cursor_.end = textString.length();
      flushLayer();
    }
    eventCount_++;
    *stopPropagation = true;
    RNS_LOG_DEBUG("TextInput text " << textString);
    textInputMetrics.contentSize.width = paragraph_->getMaxIntrinsicWidth();
    textInputMetrics.contentSize.height = paragraph_->getHeight();
    textInputMetrics.text = textString;
    textInputMetrics.eventCount = eventCount_;
    textInputEventEmitter->onKeyPress(keyPressMetrics);
    textInputEventEmitter->onChange(textInputMetrics);
    textInputEventEmitter->onContentSizeChange(textInputMetrics);
    textInputEventEmitter->onSelectionChange(textInputMetrics);
  }//else if (isInEditingMode_)
}
void RSkComponentTextInput::workerThread(){
  std::string textString = {};
  struct cursor lCursor;
  RNS_LOG_DEBUG("Creating the thread worker thread");
  KeyPressMetrics keyPressMetrics;
  TextInputMetrics textInputMetrics;
  auto component = getComponentData();
  auto textInputEventEmitter = std::static_pointer_cast<TextInputEventEmitter const>(component.eventEmitter);
  while(!isThreadWantToExit_){
    if(!inputQueue.empty()){
      RNS_LOG_DEBUG("[workerThread] I am inside the Queue ");
      mtx.lock();
      lCursor.locationFromEnd = cursor_.locationFromEnd;
      textString = displayString_;
      lCursor.end = textString.length();
      auto eventKeyType = inputQueue.front();
      RNS_LOG_DEBUG("[workerThread]event Key Type  "<<RNSKeyMap[eventKeyType]);
      mtx.unlock();
      keyPressMetrics.text = RNSKeyMap[eventKeyType];
      if ((eventKeyType >= RNS_KEY_1 && eventKeyType <= RNS_KEY_z)) {
        if (lCursor.locationFromEnd != 0){
          textString.insert(lCursor.end-lCursor.locationFromEnd,keyPressMetrics.text);
        }
        else {
          textString = textString+keyPressMetrics.text;
        }
        RNS_LOG_DEBUG("Added to the text string");
      }else {
        switch(eventKeyType){
          case RNS_KEY_Left:
            if(lCursor.locationFromEnd < lCursor.end ){
              lCursor.locationFromEnd++; // locationFromEnd
              RNS_LOG_DEBUG("Right key pressed cursor_.locationFromEnd = "<<lCursor.locationFromEnd);
              cursor_.locationFromEnd = lCursor.locationFromEnd;
            }
            keyPressMetrics.eventCount = eventCount_;
            textInputEventEmitter->onKeyPress(keyPressMetrics);
            flushLayer();
            if(!inputQueue.empty())
              inputQueue.pop();
            continue;
          case RNS_KEY_Right:
            if (lCursor.locationFromEnd>0){
              lCursor.locationFromEnd--;
              cursor_.locationFromEnd = lCursor.locationFromEnd;
              RNS_LOG_DEBUG("Right key pressed cursor_.locationFromEnd = "<<lCursor.locationFromEnd);
            }
            keyPressMetrics.eventCount = eventCount_;
            textInputEventEmitter->onKeyPress(keyPressMetrics);
            flushLayer();
            if(!inputQueue.empty())
              inputQueue.pop();
            continue;
          case RNS_KEY_Back:
          case RNS_KEY_Delete:
            mtx.lock();
            RNS_LOG_INFO("I am calling the erase function");
            if (!textString.empty() && (lCursor.end!=lCursor.locationFromEnd) )
              textString.erase(textString.begin()+(lCursor.end-lCursor.locationFromEnd-1)); //acts like a backspace.
              RNS_LOG_INFO("After removing a charector in string = "<<textString);
            mtx.unlock(); 
            break;
          default:
            if(!inputQueue.empty())
              inputQueue.pop();
            continue;//noop
        }
      }
      RNS_LOG_INFO("calling Async display to the text string");
      //currently selection is not supported selectionRange length is 
      //is always 0 & selectionRange.location always end
      mtx.lock(); 
      textInputMetrics.selectionRange.location = cursor_.end ;
      mtx.unlock();
      textInputMetrics.selectionRange.length = 0;
      RNS_LOG_INFO("checking the Async Display");
      eventCount_++;
      RNS_LOG_INFO("TextInput text " << textString);
      textInputMetrics.contentSize.width = paragraph_->getMaxIntrinsicWidth();
      textInputMetrics.contentSize.height = paragraph_->getHeight();
      textInputMetrics.text = textString;
      textInputMetrics.eventCount = eventCount_;
      textInputEventEmitter->onKeyPress(keyPressMetrics);
      textInputEventEmitter->onChange(textInputMetrics);
      textInputEventEmitter->onContentSizeChange(textInputMetrics);
      textInputEventEmitter->onSelectionChange(textInputMetrics);
      RNS_LOG_INFO("[worker thread ] waiting the semaphore ");
      sem_wait(&mutex);
      mtx.lock();
      if(!inputQueue.empty())
        inputQueue.pop();
      mtx.unlock();
    }//if(queue not empty)
    //else{ //unComment only for Debuging. 
       //RNS_LOG_INFO("[worker thread] Queue is empty ");
    //  usleep(5000);
    //}
  }//while(1)
}

RnsShell::LayerInvalidateMask  RSkComponentTextInput::updateComponentProps(const ShadowView &newShadowView,bool forceUpadate){
  auto const &textInputProps = *std::static_pointer_cast<TextInputProps const>(newShadowView.props);
  int mask = RnsShell::LayerInvalidateNone;
  std::string textString{};
  RNS_LOG_DEBUG("event count "<<textInputProps.mostRecentEventCount);
  textString = textInputProps.text;
  if(textString != displayString_) {
    mtx.lock();
    displayString_ = textString;
    cursor_.end = textString.length();
    mtx.unlock();
    if(!forceUpadate ){
      sem_post(&mutex);
    }
    mask |= LayerPaintInvalidate;
  }

  if ((textInputProps.placeholder.size()) 
      && ((placeholderString_) != (textInputProps.placeholder)) 
      &&(!textInputProps.value.has_value())) {

    placeholderString_ = textInputProps.placeholder.c_str();
    if(!displayString_.size()) {
      mask |= LayerPaintInvalidate;
    }
  }

  if(textInputProps.placeholderTextColor != placeholderColor_ ) {
    placeholderColor_ = textInputProps.placeholderTextColor;
    if(!displayString_.size()) {
      mask |= LayerPaintInvalidate;
    }
  }

  if (textInputProps.selectionColor != selectionColor_) {
    selectionColor_ = textInputProps.selectionColor;
    cursorPaint_.setColor(RSkColorFromSharedColor(selectionColor_, SK_ColorBLUE));
    mask |= LayerPaintInvalidate;
  }

  if (textInputProps.editable != editable_) {
    editable_ = textInputProps.editable;
    mask |= LayerPaintInvalidate;
  }

  if (false == caretHidden_ && true == editable_){
    caretHidden_ = false;
  } else {
    caretHidden_ = true;
  }

  return (RnsShell::LayerInvalidateMask)mask;
}
void RSkComponentTextInput::handleCommand(std::string commandName,folly::dynamic args){
  if(commandName == "setTextAndSelection"){
    //RNS_LOG_INFO("Calling Dyanic args"<<args[0].asInt());
    RNS_LOG_INFO("Calling Dyanic args"<<args[1].getString());
    mtx.lock();
    displayString_ = args[1].getString();
    mtx.unlock();
    flushLayer();
    if(!isThreadWantToExit_)
      sem_post(&mutex);
  }
}
} // namespace react
} // namespace facebook
