/**
 * \file HubertFactory.h
 *
 * \author Justin Vesche
 *
 * Factory class that builds the Hubert character
 */

#pragma once
#include "ActorFactory.h"

/**
* Factory class that builds the Hubert character
*/
class CHubertFactory : public CActorFactory
{
public:
	virtual std::shared_ptr<CActor> Create() override;
};

