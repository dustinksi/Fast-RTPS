/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This generated file is licensed to you under the terms described in the
 * fastcdr_LICENSE file included in this fastcdr distribution.
 *
 *************************************************************************
 * 
 * @file OwnershipTestPubSubMain.cpp
 * This file acts as a main entry point to the application.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include "OwnershipTestPublisher.h"
#include "OwnershipTestSubscriber.h"


#include <fastrtps/Domain.h>
#include <fastrtps/utils/RTPSLog.h>
#include <sstream>

using namespace eprosima;
using namespace eprosima::fastrtps;

int main(int argc, char** argv)
{
	Log::setVerbosity(VERB_ERROR);
	cout << "Starting " << endl;
	int type = 1;
	if (argc > 1)
	{
		if (strcmp(argv[1], "publisher") == 0)
		{
			type = 1;
		}
		else if (strcmp(argv[1], "subscriber") == 0)
		{
			type = 2;
		}
	}
	else
	{
		cout << "publisher OR subscriber argument needed" << endl;
		return 0;
	}
	
	// Register the type being used
	
	
	switch(type)
	{
		case 1:
		{
			OwnershipTestPublisher mypub; 

         // Takes an optional second parameter with the publisher ownership strength.
         // If left out, will default to strength 10.
         if (argc > 2)
         {
            std::stringstream ss(argv[2]);
            int ownershipStrength;
            ss >> ownershipStrength;
            if (!ss.fail())
               mypub.setOwnershipStrength(ownershipStrength);
         }
			if (mypub.init())
			{
				mypub.run();
			}
			break;
		}
		case 2:
		{
			OwnershipTestSubscriber mysub;
			if (mysub.init())
			{
				mysub.run();
			}
			break;
		}
	}
	
	return 0;
}
