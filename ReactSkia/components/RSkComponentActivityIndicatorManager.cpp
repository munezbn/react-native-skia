/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/components/RSkComponentActivityIndicatorManager.h"

std::mutex mutex_;

namespace facebook {
namespace react {

RSkComponentActivityIndicatorManager *RSkComponentActivityIndicatorManager::activityIndicatorManager_{nullptr};

RSkComponentActivityIndicatorManager::RSkComponentActivityIndicatorManager(){
  animRequest_ = new RnsJsRequestAnimation([this](double timestamp){
    RNS_LOG_DEBUG("[" << this->animRequest_ << "] Register Activity Indicator request Animation callback [" << timestamp << "]");
    handleActivityIndicatorAnimation(timestamp);
  });
}

RSkComponentActivityIndicatorManager* RSkComponentActivityIndicatorManager::getActivityIndicatorManager(){
  std::lock_guard<std::mutex> lock(mutex_);
  if (activityIndicatorManager_ == nullptr){
    activityIndicatorManager_ = new RSkComponentActivityIndicatorManager;
  }
  return activityIndicatorManager_;
}

void RSkComponentActivityIndicatorManager::addComponent(std::weak_ptr<RSkComponent> candidate){
  std::shared_ptr<RSkComponent> component = candidate.lock();

  if(component && component->layer().get()){
    aiComponentList_.push_back(candidate);

    if(aiComponentList_.size() == 1){
      animRequest_->start();
    }
  } 
}

void RSkComponentActivityIndicatorManager::removeComponent(Tag tag){
  std::vector<std::weak_ptr<RSkComponent>>::iterator iter;

  if(aiComponentList_.size() == 0){
    return;
  }

  for(iter = aiComponentList_.begin(); iter != aiComponentList_.end(); iter++){
    std::shared_ptr<RSkComponent> component = iter->lock();
    if(component){
      if(component->getComponentData().tag == tag){
        aiComponentList_.erase(iter);
        break;
      }
    }
  }

  if(aiComponentList_.size() == 0){
    animRequest_->stop();
  } 
}

void RSkComponentActivityIndicatorManager::handleActivityIndicatorAnimation(double timestamp){
  std::vector<std::weak_ptr<RSkComponent>>::iterator iter = aiComponentList_.begin();
  std::shared_ptr<RSkComponent> firstComponent = iter->lock();

  if(aiComponentList_.size() == 0){
    return;
  }

  if(firstComponent){
    std::shared_ptr<RnsShell::Layer> layer = firstComponent->layer();
    SkMatrix matrix;
    unsigned int arcAngle;

    if(layer.get() != nullptr){
      layer->client().notifyFlushBegin();

      for( auto & iter : aiComponentList_){
        std::shared_ptr<RSkComponent> component = iter.lock();

        if(component && component->layer().get() != nullptr){
          RSkComponentActivityIndicator *aiComponent =  dynamic_cast<RSkComponentActivityIndicator*>(component.get());

          arcAngle = aiComponent->getCurrentAngle();  
          arcAngle = (arcAngle + 6 ) % 360;
          matrix.setRotate(arcAngle, 0, 0);
          aiComponent->setCurrentAngle(arcAngle);
          
          component->layer()->transformMatrix = matrix;
          component->layer()->invalidate( RnsShell::LayerLayoutInvalidate);
        }
      }

      layer->client().notifyFlushRequired();
    }
  }
}

RSkComponentActivityIndicatorManager::~RSkComponentActivityIndicatorManager(){
  delete activityIndicatorManager_;
  activityIndicatorManager_ = nullptr;
}

} // namespace react
} // namespace facebook
