//! All Role enums

//! All Types of roles
enum ERoleTypes7R
{
	SquadRoles = 1,
	PlatoonRoles = 2,
	EchoRoles = 3,
	SierraRoles = 4,
	FoxtrotRoles = 5,
	MikeRoles = 6,
	LimaRoles = 7,
	AviationRoles = 8
}

// Global array for iteration, realised too late iterating over enums is not a thing in Enfusion Script
ref array<int> g_aERoleTypes7R = {
    ERoleTypes7R.SquadRoles,
    ERoleTypes7R.PlatoonRoles,
    ERoleTypes7R.EchoRoles,
    ERoleTypes7R.SierraRoles,
    ERoleTypes7R.FoxtrotRoles,
    ERoleTypes7R.MikeRoles,
    ERoleTypes7R.LimaRoles,
    ERoleTypes7R.AviationRoles
};


//! All squads in 7R
enum ESquads7R
{
	Platoon = 0,		//! <Platoon>
	Alpha = 1,			//! <Alpha Squad>
	Bravo = 2,			//! <Bravo Squad>
	Charlie = 3,		//! <Charlie Squad>
	Delta = 4,			//! <Delta Squad>
	Echo1 = 5,			//! <Echo-1 Squad>
	Echo2 = 6,			//! <Echo-1 Squad>
	Sierra1 = 7,		//! <Sierra-1 Squad>
	Sierra2 = 8,		//! <Sierra-2 Squad>
}


//! All Infantry Squads in 7R
enum EInfSquads7R
{
	Alpha = 1,			//! <Alpha Squad>
	Bravo = 2,			//! <Bravo Squad>
	Charlie = 3,		//! <Charlie Squad>
	Delta = 4,			//! <Delta Squad>
}


enum ESquadRoles7R
{
	// Basic Roles

	SquadLeader = 1,		//! <Squad Leader Role>
	SquadRifleman = 2,		//! <Squad Rifleman Role>
	SquadAR = 3,			//! <Squad AR Role>
	SquadLAT = 4,			//! <Squad LAT Role>
	SquadMedic = 10,		//! <Squad Medic Role>
	
	// Engineer Roles
	
	SquadEngDemo = 20,		//! <Squad Engineer (Demo) Role>
	SquadEngEOD = 21,		//! <Squad Engineer (EOD) Role>
	SquadEngFort = 22,		//! <Squad Engineer (Fortification) Role>
	SquadEngRepair = 23,	//! <Squad Engineer (Repair) Role>
	
	// Specialist Roles
	
	SquadGrenadier = 40,	//! <Squad Grenadier Role>
	SquadDMR = 41,			//! <Squad DMR Role>
	SquadBattleRifle = 42,	//! <Squad BattleRifle Role>
	SquadSpecialist = 43,	//! <Squad Specialist Role>
	SquadBreacher = 44,		//! <Squad Breacher Role>
	
	// Heavy Weapons Roles
	
	SquadMMG = 60,			//! <Squad MMG Role>
	SquadMMGAsst = 61,		//! <Squad MMG Assistant Role>
	SquadMAT = 62,			//! <Squad MAT Role>
	SquadMATAsst = 63,		//! <Squad MAT Assistant Role>
	SquadHAT = 64,			//! <Squad HAT Role>
	SquadHATAsst = 65,		//! <Squad HAT Assistant Role>
}

// Global array for EPlatoonRoles7R iteration
ref array<int> g_aESquadRoles7R = {
    ESquadRoles7R.SquadLeader,
    ESquadRoles7R.SquadRifleman,
    ESquadRoles7R.SquadAR,
    ESquadRoles7R.SquadLAT,
    ESquadRoles7R.SquadMedic,
    ESquadRoles7R.SquadEngDemo,
    ESquadRoles7R.SquadEngEOD,
    ESquadRoles7R.SquadEngFort,
    ESquadRoles7R.SquadEngRepair,
    ESquadRoles7R.SquadGrenadier,
    ESquadRoles7R.SquadDMR,
    ESquadRoles7R.SquadBattleRifle,
    ESquadRoles7R.SquadSpecialist,
    ESquadRoles7R.SquadBreacher,
    ESquadRoles7R.SquadMMG,
    ESquadRoles7R.SquadMMGAsst,
    ESquadRoles7R.SquadMAT,
    ESquadRoles7R.SquadMATAsst,
    ESquadRoles7R.SquadHAT,
    ESquadRoles7R.SquadHATAsst
};


enum EPlatoonRoles7R
{
	// Basic roles
	
	PlatoonLeader = 1,		//! <Platoon Leader Role>
	PlatoonDMR = 2,			//! <Platoon DMR Role>
	PlatoonDriver = 3,		//! <Platoon Driver Role>
	PlatoonAR = 4,			//! <Platoon AR Role>
	PlatoonMedic = 10,		//! <Platoon Medic Role>
	
	// Engineer roles
	
	PlatoonEngDemo = 20,	//! <Platoon Engineer (Demo) Role>
	PlatoonEngEOD = 21,		//! <Platoon Engineer (EOD) Role>
	PlatoonEngFort = 22,	//! <Platoon Engineer (Fortification) Role>
	PlatoonEngRepair = 23,	//! <Platoon Engineer (Repair) Role>
	
	// Specialist roles
	
	PlatoonFAC = 40,		//! <Platoon FAC Role>
	PlatoonUAV = 41,		//! <Platoon Drone Operator Role>
	
	// Heavy Weapons Roles
	
	PlatoonMMG = 60,		//! <Platoon MMG Role>
	PlatoonMMGAsst = 61,	//! <Platoon MMG Assistant Role>
	PlatoonMAT = 62,		//! <Platoon MAT Role>
	PlatoonMATAsst = 63,	//! <Platoon MAT Assistant Role>
	PlatoonHAT = 64,		//! <Platoon HAT Role>
	PlatoonHATAsst = 65,	//! <Platoon HAT Assistant Role>
}

// Global array for EPlatoonRoles7R iteration
ref array<int> g_aEPlatoonRoles7R = {
    EPlatoonRoles7R.PlatoonLeader,
    EPlatoonRoles7R.PlatoonDMR,
    EPlatoonRoles7R.PlatoonDriver,
    EPlatoonRoles7R.PlatoonAR,
    EPlatoonRoles7R.PlatoonMedic,
    EPlatoonRoles7R.PlatoonEngDemo,
    EPlatoonRoles7R.PlatoonEngEOD,
    EPlatoonRoles7R.PlatoonEngFort,
    EPlatoonRoles7R.PlatoonEngRepair,
    EPlatoonRoles7R.PlatoonFAC,
    EPlatoonRoles7R.PlatoonUAV,
    EPlatoonRoles7R.PlatoonMMG,
    EPlatoonRoles7R.PlatoonMMGAsst,
    EPlatoonRoles7R.PlatoonMAT,
    EPlatoonRoles7R.PlatoonMATAsst,
    EPlatoonRoles7R.PlatoonHAT,
    EPlatoonRoles7R.PlatoonHATAsst
};


enum EEchoRoles7R
{
	// Basic roles
	
	EchoLeader = 1,			//! <Echo Leader Role>
	EchoDMR = 2,			//! <Echo DMR Role>
	EchoDriver = 3,			//! <Echo Driver Role>
	EchoAR = 4,				//! <Echo AR Role>
	EchoMedic = 10,			//! <Echo Medic Role>
	
	// Engineer roles
	
	EchoEngDemo = 20,		//! <Echo Engineer (Demo) Role>
	EchoEngEOD = 21,		//! <Echo Engineer (EOD) Role>
	EchoEngFort = 22,		//! <Echo Engineer (Fortification) Role>
	EchoEngRepair = 23,		//! <Echo Engineer (Repair) Role>
	
	// Specialist roles
	
	EchoFAC = 40,			//! <Echo FAC Role>
	EchoUAV = 41,			//! <Echo Drone Operator Role>
	
	// Heavy Weapons Roles
	
	EchoMMG = 60,			//! <Echo MMG Role>
	EchoMMGAsst = 61,		//! <Echo MMG Assistant Role>
	EchoMAT = 62,			//! <Echo MAT Role>
	EchoMATAsst = 63,		//! <Echo MAT Assistant Role>
	EchoHAT = 64,			//! <Echo HAT Role>
	EchoHATAsst = 65,		//! <Echo HAT Assistant Role>
}

// Global array for EEchoRoles7R iteration
ref array<int> g_aEEchoRoles7R = {
    EEchoRoles7R.EchoLeader,
    EEchoRoles7R.EchoDMR,
    EEchoRoles7R.EchoDriver,
    EEchoRoles7R.EchoAR,
    EEchoRoles7R.EchoMedic,
    EEchoRoles7R.EchoEngDemo,
    EEchoRoles7R.EchoEngEOD,
    EEchoRoles7R.EchoEngFort,
    EEchoRoles7R.EchoEngRepair,
    EEchoRoles7R.EchoFAC,
    EEchoRoles7R.EchoUAV,
    EEchoRoles7R.EchoMMG,
    EEchoRoles7R.EchoMMGAsst,
    EEchoRoles7R.EchoMAT,
    EEchoRoles7R.EchoMATAsst,
    EEchoRoles7R.EchoHAT,
    EEchoRoles7R.EchoHATAsst
};


enum ESierraRoles7R
{
	// Basic roles
	
	SierraLeader = 1,		//! <Sierra Leader Role>
	SierraSpotter = 2,		//! <Sierra Spotter Role>
	SierraDMR1 = 3,			//! <Sierra DMR 1 Role>
	SierraDMR2 = 4,			//! <Sierra DMR 2 Role>
	SierraSniper1 = 5,		//! <Sierra Sniper 1 Role>
	SierraSniper2 = 6,		//! <Sierra Sniper 2 Role>
	SierraRecon = 7,		//! <Sierra Recon Role>
	
	// Specialist roles
	
	SierraFAC = 10,			//! <Sierra FAC Role>
	SierraUAV = 11,			//! <Sierra Drone Operator Role>
}

// Global array for ESierraRoles7R iteration
ref array<int> g_aESierraRoles7R = {
    ESierraRoles7R.SierraLeader,
    ESierraRoles7R.SierraSpotter,
    ESierraRoles7R.SierraDMR1,
    ESierraRoles7R.SierraDMR2,
    ESierraRoles7R.SierraSniper1,
    ESierraRoles7R.SierraSniper2,
    ESierraRoles7R.SierraRecon,
    ESierraRoles7R.SierraFAC,
    ESierraRoles7R.SierraUAV
};


enum EFoxtrotRoles7R
{
	FoxtrotCO = 1,			//! <Foxtrot Commander Role>
	FoxtrotTech = 2,		//! <Foxtrot Technician Role>
	FoxtrotCrew = 3,		//! <Foxtrot Crewman Role>
}

// Global array for EFoxtrotRoles7R iteration
ref array<int> g_aEFoxtrotRoles7R = {
    EFoxtrotRoles7R.FoxtrotCO,
    EFoxtrotRoles7R.FoxtrotTech,
    EFoxtrotRoles7R.FoxtrotCrew
};


enum EMikeRoles7R
{
	MikeCO = 1,				//! <Mike Commander Role>
	MikeTech = 2,			//! <Mike Technician Role>
	MikeCrew = 3,			//! <Mike Crewman Role>
}

// Global array for EMikeRoles7R iteration
ref array<int> g_aEMikeRoles7R = {
    EMikeRoles7R.MikeCO,
    EMikeRoles7R.MikeTech,
    EMikeRoles7R.MikeCrew
};


enum ELimaRoles7R
{
	// Basic roles
	
	LimaLeader = 1,			//! <Lima Leader Role>
	LimaDriver = 2,			//! <Lima Driver Role>
	
	// Engineer roles
	
	LimaEngDemo = 10,		//! <Lima Engineer (Demo) Role>
	LimaEngEOD = 11,		//! <Lima Engineer (EOD) Role>
	LimaEngFort = 12,		//! <Lima Engineer (Fortification) Role>
	LimaEngRepair = 13,		//! <Lima Engineer (Repair) Role>
}

// Global array for ELimaRoles7R iteration
ref array<int> g_aELimaRoles7R = {
    ELimaRoles7R.LimaLeader,
    ELimaRoles7R.LimaDriver,
    ELimaRoles7R.LimaEngDemo,
    ELimaRoles7R.LimaEngEOD,
    ELimaRoles7R.LimaEngFort,
    ELimaRoles7R.LimaEngRepair
};


enum EAviationRoles7R
{
	RodeoPilot = 1,			//! <Rodeo Pilot Role>
	RodeoCoPilot = 2,		//! <Rodeo Co-Pilot Role>
	
	WhiskeyPilot = 10,		//! <Whiskey Pilot>
}

// Global array for EAviationRoles7R iteration
ref array<int> g_aEAviationRoles7R = {
    EAviationRoles7R.RodeoPilot,
    EAviationRoles7R.RodeoCoPilot,
    EAviationRoles7R.WhiskeyPilot
};
