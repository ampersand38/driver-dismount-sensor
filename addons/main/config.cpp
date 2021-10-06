#include "script_component.hpp"

class CfgPatches {
    class DriverDismountSensor {
        name = "Driver Dismount Sensor";
        units[] = {};
        weapons[] = {};
        requiredVersion = 2.0;
        requiredAddons[] = {"A3_Data_F_AoW_Loadorder", "A3_Data_F_Mod_Loadorder"};
        author = "Ampersand";
        authors[] = {"Ampersand"};
        authorUrl = "https://github.com/ampersand38/driver-dismount-sensor";
    };
};

class SensorTemplateMan;
class DefaultVehicleSystemsDisplayManagerLeft {
    class Components;
};
class DefaultVehicleSystemsDisplayManagerRight {
    class Components;
};
class VehicleSystemsTemplateLeftDriver: DefaultVehicleSystemsDisplayManagerLeft {
	class Components: Components
	{
        class SensorsDisplay {
            componentType = "SensorsDisplayComponent";
            range[] = {15};	// accepts an integer or an array of available ranges (submode)
            showTargetTypes = 1+2+4+8+16+32+64+128+256+512+1024; // 1 - Sensor sectors, 2 - Threats, 4 - Marked tgt symbol, 8 - Own detection, 16 - Remote detection, 32 - Active detection, 64 - Passive detection, 128 - Ground tgts, 256 - Air tgts, 512 - Men, 1024 - Special (laser, NV)
            resource = "RscCustomInfoSensors";
        };
	};
};
class VehicleSystemsTemplateRightDriver: DefaultVehicleSystemsDisplayManagerRight {
	class Components: Components
	{
        class SensorsDisplay {
            componentType = "SensorsDisplayComponent";
            range[] = {15};	// accepts an integer or an array of available ranges (submode)
            showTargetTypes = 1+2+4+8+16+32+64+128+256+512+1024; // 1 - Sensor sectors, 2 - Threats, 4 - Marked tgt symbol, 8 - Own detection, 16 - Remote detection, 32 - Active detection, 64 - Passive detection, 128 - Ground tgts, 256 - Air tgts, 512 - Men, 1024 - Special (laser, NV)
            resource = "RscCustomInfoSensors";
        };
	};
};

#define SENSORMAN class SensorsManagerComponent { \
   class Components { \
       class SensorMan : SensorTemplateMan { \
           class AirTarget \
           { \
               minRange = 0; \
               maxRange = 10; \
               viewDistanceLimitCoef	= 1; \
               objectDistanceLimitCoef	= 1;	 \
           }; \
           class GroundTarget \
           { \
               minRange = 0; \
               maxRange = 10; \
               viewDistanceLimitCoef = 1; \
               objectDistanceLimitCoef = 1; \
           }; \
           allowsMarking = 0; \
           angleRangeHorizontal = 360; \
       }; \
   }; \
};

#define ADDSENSOR class Components { \
    SENSORMAN \
};

#define ADDPANELSENSOR class Components { \
    class VehicleSystemsDisplayManagerComponentLeft: VehicleSystemsTemplateLeftDriver {}; \
    class VehicleSystemsDisplayManagerComponentRight: VehicleSystemsTemplateRightDriver {}; \
    SENSORMAN \
};

class CfgVehicles {
    class Tank;
    class Tank_F : Tank {
        ADDSENSOR
    };
    class MBT_04_base_F;
    class MBT_04_command_base_F : MBT_04_base_F {
        ADDPANELSENSOR
    };
    class Car;
    class Car_F : Car {
        ADDSENSOR
    };
    class Wheeled_APC_F : Car_F {
        ADDSENSOR
    };
    class AFV_Wheeled_01_base_F : Wheeled_APC_F {
        ADDPANELSENSOR
    };
};
