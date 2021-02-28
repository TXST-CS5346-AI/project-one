#!/bin/bash

rm vehicle_diagnosis.log 2>/dev/null

chmod -R 755 *
make
./VehicleRepairAndDiagnosis | tee vehicle_diagnosis.log
