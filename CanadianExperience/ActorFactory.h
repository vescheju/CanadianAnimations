/**
 * \file ActorFactory.h
 *
 * \author Justin Vesche
 *
 * Abstract base class for actor factories. 
 */

#pragma once
#include<memory>
class CActor;

/**
* Abstract base class for actor factories.
*/
class CActorFactory
{
public:
	/** create an actor
	* \returns an actor*/
	virtual std::shared_ptr<CActor> Create() = 0;
};

