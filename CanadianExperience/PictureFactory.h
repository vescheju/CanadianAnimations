/**
 * \file PictureFactory.h
 *
 * \author Justin Vesche
 *
 * A factory class that builds our picture.
 */

#pragma once
#include<memory>
class CPicture;

/**
* A factory class that builds our picture.
*/
class CPictureFactory
{
public:
	std::shared_ptr<CPicture> Create();


};

