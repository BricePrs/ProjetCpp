//
// Created by brice on 20/05/23.
//

#ifndef TP_PERESB_HASSANH_SIMULATIONSETTING_H
#define TP_PERESB_HASSANH_SIMULATIONSETTING_H

enum BoundaryBehaviour {
    Reflexive,
    ReflexivePotential,
    Absorption,
    Periodic,
};

struct PhysicsConstants {
    double   g                                             = -9.81;	        ///< g constant (positive means upward force )
    double   eps                                           = 1.;	        ///< epsilon constant
    double   sigma                                         = 1.;	        ///< sigma constant
};

struct SimulationSettings {
    bool                external_gravity                   = false;		    ///< Should the external gravity be applied
    bool                gravitational_interaction          = false;		    ///< Should the gravitational interaction be applied
    bool                lennard_jones_interaction          = false;		    ///< Should the Lennard-Jones interaction be applied
    double              goal_kinetic_energy                = -1;   		    ///< The kinetic energy goal set by the user to force the system's kinetic energy to this level every 1000 physics iterations
    double              physics_time_step                  = -1.;  		    ///< The time step used in the physics simulation
    double              physics_time_total                 = -1.;  		    ///< The total time for the physics simulation
    uint32_t            iter_count_until_save              = 0;    		    ///< The number of iterations until saving the simulation
    uint32_t            iter_count_until_balance_energy    = 1000;			///< The number of iterations until balancing the system's kinetic energy
    BoundaryBehaviour   boundary_behaviour                 = Absorption;	///< Particle behavior if outside of boundaries
    PhysicsConstants constants;                                             ///< Constants used for the physics simulation
};


#endif //TP_PERESB_HASSANH_SIMULATIONSETTING_H
