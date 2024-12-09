#include "device.h"

class Devices {

    public:

        Devices(Device* _devices,int _count) : devices(_devices), count(_count) {}

        void update() {

            total_consumption = 0;
            total_cost = 0;

            for(int i = 0; i < count; i++) {

                devices[i].update();
                total_consumption += devices[i].units_consumed;
                total_cost += devices[i].cost;
            }
        }

        Device& get(String name) {

            int i = 0;
            while (devices[i].name != name) i++;
            return devices[i];
        }

        int get_count() {

            return count;
        }

        Device& operator[] (int i) {

            return devices[i];
        }

        double total_consumption = 0;
        double total_cost = 0;

    private:
        Device *devices;
        int count;
};
