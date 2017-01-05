/*
 * Dragable.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#include "Draggable.h"

#include <cocos2d.h>

#include <component/touch/drag/OnDragEvent.h>
#include <component/ComponentManager.h>
#include <component/builder/Flags.h>
#include <component/touch/TouchableEvents.h>

namespace Dexode
{
namespace Component
{

void Draggable::onTouchBegan(cocos2d::Touch* touch)
{
	_startPosition = getWorkingNode()->getPosition();
	if (_onTouchBegan)
	{
		OnDragEvent event;
		event.node = getWorkingNode();
		event.touch = touch;
		event.startPosition = _startPosition;
		_onTouchBegan(event);
	}
}

void Draggable::onTouchMoved(cocos2d::Touch* touch)
{
	if ((_flags & Config::Draggable::MOVING_ONLY_X) != 0)
	{
		getWorkingNode()->setPositionX(_startPosition.x - (touch->getStartLocation().x - touch->getLocation().x));
	}
	else
	{
		getWorkingNode()->setPosition(_startPosition - (touch->getStartLocation() - touch->getLocation()));
	}

	if (_onTouchMoved)
	{
		OnDragEvent event;
		event.node = getWorkingNode();
		event.touch = touch;
		event.startPosition = _startPosition;
		_onTouchMoved(event);
	}
}

void Draggable::onTouchEnded(cocos2d::Touch* touch)
{
	if ((_flags & Config::Draggable::DO_NOT_RESTORE_POSITION_ON_END)
		!= Config::Draggable::DO_NOT_RESTORE_POSITION_ON_END)
	{
		getWorkingNode()->setPosition(_startPosition);
	}

	if (_onTouchEnded)
	{
		OnDragEvent event;
		event.node = getWorkingNode();
		event.touch = touch;
		event.startPosition = _startPosition;
		_onTouchEnded(event);
	}
}

void Draggable::setListeners(const OnTouch& onTouchBegan, const OnTouch& onTouchMoved, const OnTouch& onTouchEnded)
{
	_onTouchBegan = onTouchBegan;
	_onTouchMoved = onTouchMoved;
	_onTouchEnded = onTouchEnded;
}

void Draggable::setFlags(int flags)
{
	_flags = flags;
}

void Draggable::onAttach()
{
	inherited::onAttach();
	_collector = listenForTouches(this);
}

void Draggable::onDetach()
{
	_collector.unlistenAll();
	inherited::onDetach();
}

} /* namespace Component */
} /* namespace Dexode */