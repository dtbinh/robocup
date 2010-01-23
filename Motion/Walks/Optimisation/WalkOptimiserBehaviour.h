/*! @file WalkOptimiserBehaviour.h
    @brief Declaration of WalkOptimiserBehaviour class
 
    @class WalkOptimiserBehaviour
    @brief A module to provide control the robot while walk optimisation is running
 
    @author Jason Kulk
 
  Copyright (c) 2009 Jason Kulk
 
    This file is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with NUbot.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WALKOPTIMISERBEHAVIOUR_H
#define WALKOPTIMISERBEHAVIOUR_H

#include "Behaviour/Jobs.h"
#include "Motion/NUWalk.h"
#include "NUPlatform/NUPlatform.h"
#include "NUPlatform/NUSensors/NUSensorsData.h"
#include "NUPlatform/NUActionators/NUActionatorsData.h"
#include "../WalkParameters.h"
#include "WalkOptimiser.h"

#include <string>
#include <fstream>
using namespace std;

class WalkOptimiserBehaviour
{
public:
    WalkOptimiserBehaviour(NUPlatform* p_platform, NUWalk* p_walk);
    ~WalkOptimiserBehaviour();
    
    void process(NUSensorsData* data, NUActionatorsData* actions);
    void process(JobList& joblist);
    
    void summaryTo(ostream& output);
    void csvTo(ostream& output);
protected:
    void startTrial();
    void measureCost();
    void finishMeasureCost();
    void measureRobust();
    void finishMeasureRobust();
    
    void perturbRobot();
    void pushInward();
    void pushOutward();
    void pushForward();
    void pushBackward();
    void pushJoint(NUSensorsData::joint_id_t id, float offset);

    void respawn();
    
    void tickOptimiser(float metric);
    void loadOptimiser();
    void saveOptimiser();
private:
public:
protected:
private:
    NUSensorsData* m_data;
    NUActionatorsData* m_actions;
    
    NUWalk* m_walk;
    WalkParameters m_walk_parameters;
    WalkOptimiser* m_optimiser;
    
    enum State 
    {
        Initial,
        StartCost,
        MeasureCost,
        StartRobust,
        MeasureRobust
    };
    State m_state, m_previous_state;
    float m_respawn_x, m_respawn_y, m_respawn_bearing;
    double m_last_respawn_time;
    float m_target_speed;
    float m_target_trial_duration;
    
    double m_trial_start_time;
    float m_trial_start_x, m_trial_start_y;
    float m_trial_energy_used, m_trial_perturbation_mag;
    int m_perturbation_direction;
    float m_left_impact_time, m_right_impact_time;
    
    enum metric_type_t
    {
        Speed,
        Cost,
        SpeedAndPushes,
        CostAndPushes
    };
    metric_type_t m_metric_type;
    float m_measured_metric, m_measured_speed, m_measured_cost, m_measured_robustness;
    
    // Serialisation
    string m_saved_optimiser_filename;
    ofstream m_best_parameter_log;
    ofstream m_performance_log;
};

#endif

