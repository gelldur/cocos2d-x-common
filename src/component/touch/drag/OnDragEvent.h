/*
 * OnDragEvent.h
 *
 *  Created on: Feb 4, 2015
 *      Author: dawid
 */

#pragma once

#include <predeclare.h>
#include <Vec.h>

namespace Dexode
{
namespace Component
{

struct OnDragEvent
{
	cocos2d::Touch* touch;
	cocos2d::Node* node;
	cocos2d::Vec2 startPosition;
};

} /* namespace Component */
} /* namespace Dexode */
