// All 7R Roles
enum ERoles7R
{
	// 000: Infantry Squad roles
		// Base Role
		
		Base = 0,
		
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

	// 100: Platoon Squad roles

		// Basic roles
		
		PlatoonLeader = 100,	//! <Platoon Leader Role>
		PlatoonDMR = 101,		//! <Platoon DMR Role>
		PlatoonDriver = 102,	//! <Platoon Driver Role>
		PlatoonAR = 103,		//! <Platoon AR Role>
		PlatoonMedic = 110,		//! <Platoon Medic Role>
		
		// Engineer roles
		
		PlatoonEngDemo = 120,	//! <Platoon Engineer (Demo) Role>
		PlatoonEngEOD = 121,	//! <Platoon Engineer (EOD) Role>
		PlatoonEngFort = 122,	//! <Platoon Engineer (Fortification) Role>
		PlatoonEngRepair = 123,	//! <Platoon Engineer (Repair) Role>
		
		// Specialist roles
		
		PlatoonFAC = 140,		//! <Platoon FAC Role>
		PlatoonUAV = 141,		//! <Platoon Drone Operator Role>
		
		// Heavy Weapons Roles
		
		PlatoonMMG = 160,		//! <Platoon MMG Role>
		PlatoonMMGAsst = 161,	//! <Platoon MMG Assistant Role>
		PlatoonMAT = 162,		//! <Platoon MAT Role>
		PlatoonMATAsst = 163,	//! <Platoon MAT Assistant Role>
		PlatoonHAT = 164,		//! <Platoon HAT Role>
		PlatoonHATAsst = 165,	//! <Platoon HAT Assistant Role>
	
	// 200: Echo Squad roles

		// Basic roles
	
		EchoLeader = 200,		//! <Echo Leader Role>
		EchoDMR = 201,			//! <Echo DMR Role>
		EchoDriver = 202,		//! <Echo Driver Role>
		EchoAR = 203,			//! <Echo AR Role>
		EchoMedic = 210,		//! <Echo Medic Role>
		
		// Engineer roles
		
		EchoEngDemo = 220,		//! <Echo Engineer (Demo) Role>
		EchoEngEOD = 221,		//! <Echo Engineer (EOD) Role>
		EchoEngFort = 222,		//! <Echo Engineer (Fortification) Role>
		EchoEngRepair = 223,	//! <Echo Engineer (Repair) Role>
		
		// Specialist roles
		
		EchoFAC = 240,			//! <Echo FAC Role>
		EchoUAV = 241,			//! <Echo Drone Operator Role>
		
		// Heavy Weapons Roles
		
		EchoMMG = 260,			//! <Echo MMG Role>
		EchoMMGAsst = 261,		//! <Echo MMG Assistant Role>
		EchoMAT = 262,			//! <Echo MAT Role>
		EchoMATAsst = 263,		//! <Echo MAT Assistant Role>
		EchoHAT = 264,			//! <Echo HAT Role>
		EchoHATAsst = 265,		//! <Echo HAT Assistant Role>

	
	// 300: Sierra Squad roles
	
		// Basic roles
	
		SierraLeader = 300,		//! <Sierra Leader Role>
		SierraSpotter = 301,	//! <Sierra Spotter Role>
		SierraDMR1 = 302,		//! <Sierra DMR 1 Role>
		SierraDMR2 = 304,		//! <Sierra DMR 2 Role>
		SierraSniper1 = 305,	//! <Sierra Sniper 1 Role>
		SierraSniper2 = 306,	//! <Sierra Sniper 2 Role>
		SierraRecon = 307,		//! <Sierra Recon Role>
		
		// Specialist roles
		
		SierraFAC = 340,		//! <Sierra FAC Role>
		SierraUAV = 341,		//! <Sierra Drone Operator Role>
	
	// 400: Foxtrot roles
	
		FoxtrotCO = 400,		//! <Foxtrot Commander Role>
		FoxtrotTech = 401,		//! <Foxtrot Technician Role>
		FoxtrotCrew = 402,		//! <Foxtrot Crewman Role>
	
	// 500: Mike roles
	
		MikeCO = 400,			//! <Mike Commander Role>
		MikeTech = 401,			//! <Mike Technician Role>
		MikeCrew = 402,			//! <Mike Crewman Role>
	
	// 600: Lima roles
	
	// Basic roles
	
		LimaLeader = 600,		//! <Lima Leader Role>
		LimaDriver = 601,		//! <Lima Driver Role>
		
		// Engineer roles
		
		LimaEngDemo = 620,		//! <Lima Engineer (Demo) Role>
		LimaEngEOD = 621,		//! <Lima Engineer (EOD) Role>
		LimaEngFort = 622,		//! <Lima Engineer (Fortification) Role>
		LimaEngRepair = 623,	//! <Lima Engineer (Repair) Role>
	
	// 800: Aerial support roles
	
		RodeoPilot = 800,		//! <Rodeo Pilot Role>
		RodeoCoPilot = 801,		//! <Rodeo Co-Pilot Role>
		
		WhiskeyPilot = 810,		//! <Whiskey Pilot>
}
