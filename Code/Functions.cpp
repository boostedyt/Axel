#include "Functions.hpp"
#include "Natives.hpp"
#include "Hooking.hpp"

namespace Big
{

	# define M_PI 3.14159265358979323846  /* pi */
	//----------------\
	// FUNCTIONS	   |
	//----------------/

	// here is some diffrent toggle bool options
	bool Godmode = false;

	void godmode()
	{
		//-----------------------get plyer ped id; this bool Godmode is Controling is to true and false 
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), Godmode);
	}

	bool Invisible = false;

	void invisible(bool toggle)
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !toggle, false);
	}

	bool SuperJump = false;

	void superjump(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		}
	}

	bool NeverWanted = false;

	void neverwanted(bool toggle)
	{
		Player player = PLAYER::PLAYER_PED_ID();
		if (NeverWanted)
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			PLAYER::SET_MAX_WANTED_LEVEL(0);

			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);
		}
		else
		{
			PLAYER::SET_MAX_WANTED_LEVEL(5);
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);
		}
	}

	bool FireBreath = false;

	void firebreath(bool toggle)
	{
		if (toggle)
		{
			float XPos = 0.02, YPos = 0.2, ZPos = 0.0, XOff = 90.0, YOff = -100.0, ZOff = 90.0;
			STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			int ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("ent_sht_flame", PLAYER::PLAYER_PED_ID(), XPos, YPos, ZPos, XOff, YOff, ZOff, 0x796e, 1, 1, 1, 1);
			STREAMING::REMOVE_PTFX_ASSET();
		}
	}

	bool noragdoll = false;
	void Ragdoll()
	{
		Ped player_ped_id = PLAYER::PLAYER_PED_ID();
		PED::SET_PED_CAN_RAGDOLL(player_ped_id, !noragdoll);
	}

	bool Extremejump = false;
	void extremejump(bool toggle) {
		if (toggle)
		{
			int Me = PLAYER::PLAYER_PED_ID();
			if (GetAsyncKeyState(VK_SPACE))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(Me, 1, 0, 0, +3, 0, 0, 0, 1, 1, 1, 1, 0, 1);
			}
		}
	}

	bool Fastrun = false;
	void fastrun(bool toggle)
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), toggle ? 1.49f : 1.f);
	}

	bool HandTrails = false;
	void handtrails(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_L_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(255);

			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_R_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(255);
		}
	}

	bool FootTrails = false;
	void foottrails(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_L_Foot, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(footred / 255, footgreen / 255, footblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(255);

			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_R_Foot, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(footred / 255, footgreen / 255, footblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(255);
		}
	}

	bool SlideRun = false;
	void sliderun(bool toggle)
	{
		if (toggle) {
			Ped ped = PLAYER::PLAYER_PED_ID();

			if (TASK::IS_PED_RUNNING(ped) || TASK::IS_PED_SPRINTING(ped))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1, true, true, true, false, true);
			}
		}
	}

	bool NoClip = false;
	void noclip()
	{
		if (NoClip)
		{
			auto ped = PLAYER::PLAYER_PED_ID();
			Vector3 xyzcoords = ENTITY::GET_ENTITY_COORDS(ped, true);
			auto heading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING() + ENTITY::GET_ENTITY_HEADING(ped);
			auto pitch = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();

			auto speed = 1.0f;

			auto xm = -sin(heading * M_PI / 180.0);
			auto ym = cos(heading * M_PI / 180.0);
			auto zm = sin(pitch * M_PI / 180.0);

			auto len = sqrt(xm * xm + ym * ym + zm * zm);
			if (len != 0) {
				xm = xm / len;
				ym = ym / len;
				zm = zm / len;
			}

			auto x = xyzcoords.x;
			auto y = xyzcoords.y;
			auto z = xyzcoords.z;

			ENTITY::SET_ENTITY_VELOCITY(ped, 0.0001, 0.0001, 0.0001);
			if (GetAsyncKeyState(VK_SHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21)) {
				speed = speed + 3;
			}
			if (GetAsyncKeyState(0x43) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 19)) {
				speed = speed - 0.5;
			}

			//forward
			if (GetAsyncKeyState(0x57)) {
				x = x + speed * xm;
				y = y + speed * ym;
				z = z + speed * zm;
			}
			//backward
			if (GetAsyncKeyState(0x53)) {
				x = x - speed * xm;
				y = y - speed * ym;
				z = z - speed * zm;
			}

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, x, y, z, true, true, true);
		}
	}

	// here you take all your void´s that you want update loop on :)
	void FunctionsOnTick()
	{
		godmode();
		invisible(
			/*now is that bool toggle verified bt bool Invisible so this bool have now controll over invisible(bool toggle)*/
			Invisible);
		superjump(SuperJump);
		neverwanted(NeverWanted);
		firebreath(FireBreath);
		Ragdoll();
		extremejump(Extremejump);
		fastrun(Fastrun);
		handtrails(HandTrails);
		foottrails(FootTrails);
		sliderun(SlideRun);
		noclip();
	}


	std::set<Ped> lastSeenPeds;

	//=================
	// PED FUNCTIONS
	//=================

	Ped ClonePed(Ped ped)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped, 0))
		{
			return PED::CLONE_PED(ped, 1, 1, 1);
		}

		return 0;
	}

	Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle)
	{
		Ped NewPed;
		int PedHash = MISC::GET_HASH_KEY(PedName);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash))
		{
			if (STREAMING::IS_MODEL_VALID(PedHash))
			{
				STREAMING::REQUEST_MODEL(PedHash);
				while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);

				NewPed = PED::CREATE_PED(ped_type, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z,
				                         0, network_handle, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
				return NewPed;
			}
		}

		return -1;
	}

	//Animations
	void LoadAnim(char* dict)
	{
		int tick = 0;
		STREAMING::REQUEST_ANIM_DICT(dict);
		while (tick < 100 && !STREAMING::HAS_ANIM_DICT_LOADED(dict))
		{
			tick++;
			WAIT(0);
		}
	}

	void playAnimation(Ped ped, bool loop, char* dict, char* anim)
	{
		LoadAnim(dict);
		int a = -1;
		int b = 1;

		if (!loop)
		{
			a = 1;
			b = 0;
		}

		TASK::TASK_PLAY_ANIM(ped, dict, anim, 10000.0f, -1.5f, a, b, 0.445f, false, false, false);
	}

	//Skins
	bool applyChosenSkin(DWORD model)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			{
				WAIT(0);
			}

			Vehicle veh = NULL;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			}

			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			//PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), FALSE);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			WAIT(0);

			if (veh != NULL)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			}

			WAIT(100);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			return true;
		}
		return false;
	}

	bool applyChosenSkin(std::string skinName)
	{
		DWORD model = MISC::GET_HASH_KEY(skinName.c_str());
		return applyChosenSkin(model);
	}

	//CONTROL
	void RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}
	}

	void RequestControlOfEnt(Entity entity)
	{
		int tick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			tick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
		}
	}

	//FORCE
	void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
		{
			RequestControlOfEnt(e);
		}

		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
	}

	//NEARBY PEDS
	std::set<Ped> getNearbyPeds()
	{
		return lastSeenPeds;
	}

	void update_nearby_peds(Ped playerPed, int count)
	{
		const int numElements = count;
		const int arrSize = numElements * 2 + 2;

		auto peds = new Any[arrSize];
		peds[0] = numElements;
		int found = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);

		for (int i = 0; i < found; i++)
		{
			int offsettedID = i * 2 + 2;

			if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
			{
				continue;
			}

			Ped xped = peds[offsettedID];

			bool inSet = lastSeenPeds.contains(xped);
			if (!inSet)
			{
				lastSeenPeds.insert(xped);
			}
		}

		std::set<Ped>::iterator it;
		for (it = lastSeenPeds.begin(); it != lastSeenPeds.end();)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(*it))
			{
				lastSeenPeds.erase(it++);
			}
			else
			{
				++it;
			}
		}

		delete peds;
	}

	//Converts Radians to Degrees
	float degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}

	//little one-line function called '$' to convert $TRING into a hash-key:
	Hash $(std::string str)
	{
		return MISC::GET_HASH_KEY(&str[0u]);
	}

	// quick function to get - coords - of - entity:
	Vector3 coordsOf(Entity entity)
	{
		return ENTITY::GET_ENTITY_COORDS(entity, 1);
	}

	//quick function to get distance between 2 points: eg - if (distanceBetween(coordsOf(player), targetCoords) < 50)
	float distanceBetween(Vector3 A, Vector3 B)
	{
		return MISC::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
	}

	//quick "get random int in range 0-x" function:
	int rndInt(int start, int end)
	{
		return MISC::GET_RANDOM_INT_IN_RANGE(start, end);
	}

	//TELEPORTATION
	void teleport_to_coords(Entity e, Vector3 coords)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
		WAIT(0);
	}

	Vector3 get_blip_marker()
	{
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = HUD::GET_WAYPOINT_BLIP_ENUM_ID();
		for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i =
		     HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}

		return zero;
	}

	void teleport_to_marker()
	{
		Vector3 coords = get_blip_marker();

		if (coords.x == 0 && coords.y == 0)
		{
			//notifyMap("No Waypoint has been set!", 0);
			return;
		}

		// get entity to teleport
		Entity e = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
		{
			e = PED::GET_VEHICLE_PED_IS_USING(e);
		}

		// load needed map region and check height levels for ground existence
		bool groundFound = false;
		static float groundCheckHeight[] =
		{
			100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0,
			800.0
		};
		for (float& i : groundCheckHeight)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, i, 0, 0, 1);
			WAIT(100);
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, i, &coords.z, 0, false))
			{
				groundFound = true;
				coords.z += 3.0;
				break;
			}
		}
		// if ground not found then set Z in air and give player a parachute
		if (!groundFound)
		{
			coords.z = 1000.0;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}
		//do it
		teleport_to_coords(e, coords);
	}

	//In Game KEYBOARD
	std::string show_keyboard(const char* title_id, char* prepopulated_text)
	{
		DWORD time = GetTickCount() + 400;
		while (GetTickCount() < time)
		{
			WAIT(0);
		}

		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (title_id == nullptr ? "HUD_TITLE" : title_id), "",
		                                (prepopulated_text == nullptr ? "" : prepopulated_text), "", "", "", 64);

		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			WAIT(0);
		}

		std::stringstream ss;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
		{
			return std::string("");
		}
		return std::string(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
	}

	//VEHICLE
	static std::string lastvehmodel("");

	bool get_vehicle_keyboard_result(uint32_t* outModel)
	{
		std::string result = show_keyboard("FMMC_KEY_TIP", &lastvehmodel[0]);
		if (!result.empty())
		{
			uint32_t model = MISC::GET_HASH_KEY(result.c_str());
			if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				lastvehmodel = "";
				//notifyBottom("~HUD_COLOUR_RED~Not A Valid Model!");
				return false;
			}
			STREAMING::REQUEST_MODEL(model);
			DWORD now = GetTickCount();
			while (!STREAMING::HAS_MODEL_LOADED(model) && GetTickCount() < now + 5000)
			{
				WAIT(0);
			}

			if (!STREAMING::HAS_MODEL_LOADED(model))
			{
				lastvehmodel = "";
				std::ostringstream ss2;
				ss2 << "~HUD_COLOUR_RED~ Timed out requesting  " << result << " : 0x" << model;
				//				notifyBottom(ss2.str());
				return false;
			}

			lastvehmodel = result;
			*outModel = model;
			return true;
		}

		return false;
	}






	//VECTOR AND FLOAT FUNCTIONS
	Vector3 rot_to_direction(Vector3* rot)
	{
		float radiansZ = rot->z * 0.0174532924f;
		float radiansX = rot->x * 0.0174532924f;
		float num = abs(static_cast<float>(cos((double)radiansX)));
		Vector3 dir;
		dir.x = static_cast<float>((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = static_cast<float>((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = static_cast<float>(sin((double)radiansX));
		return dir;
	}

	Vector3 add(Vector3* vectorA, Vector3* vectorB)
	{
		Vector3 result;
		result.x = vectorA->x;
		result.y = vectorA->y;
		result.z = vectorA->z;
		result.x += vectorB->x;
		result.y += vectorB->y;
		result.z += vectorB->z;
		return result;
	}

	Vector3 multiply(Vector3* vector, float x)
	{
		Vector3 result;
		result.x = vector->x;
		result.y = vector->y;
		result.z = vector->z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}

	float get_distance(Vector3* pointA, Vector3* pointB)
	{
		float a_x = pointA->x;
		float a_y = pointA->y;
		float a_z = pointA->z;
		float b_x = pointB->x;
		float b_y = pointB->y;
		float b_z = pointB->z;
		double x_ba = b_x - a_x;
		double y_ba = b_y - a_y;
		double z_ba = b_z - a_z;
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return static_cast<float>(sqrt(sum_2 + z_ba));
	}

	float get_vector_length(Vector3* vector)
	{
		double x = vector->x;
		double y = vector->y;
		double z = vector->z;
		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	//NOTIFICATIONS
	/*
	Colours:
	~r~ = Red
	~b~ = Blue
	~g~ = Green
	~y~ = Yellow
	~p~ = Purple
	~o~ = Orange
	~c~ = Grey
	~m~ = Dark Grey
	~u~ = Black
	~n~ = Skip Line
	~s~ = White
	~d~ = dark blue
	~f~ = light blue
	~l~ = black
	~t~ = gray
	~v~ = black

	Fonts:
	~italic~ = italic font
	~bold~ = bold font
	*/


	// 1 WHITE
	// 2 Unknown
	// 5 Grey
	// 6 Red
	// 7 weak red
	// 8 dark red

	void notify_Custom(const char* Head_txt, const char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(/*ytd file name "DO NOT USE .ytd"*/"MH_BAse_", false);
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(/*ytd file name "DO NOT USE .ytd"*/"MH_BAse_")) WAIT(0);

		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(fmt);
		HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(
			/*ytd file name "DO NOT USE .ytd"*/"MH_BAse_", /*Texture name inside ytd file*/"Mod_Hub_Logo_Icon", false,
			                                   1, "Mod Hub", Head_txt, 1, "", 9, 0); //  can create a custom ytd icon
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(8000, 0);


		//HUD::_SET_NOTIFICATION_MESSAGE("Mod_Hub_Logo_Icon", "Mod_Hub_Logo_Icon", 1, 9, 1, Head_txt, fmt);
		/*	HUD::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("Mod_Hub_Logo_Icon", "Mod_Hub_Logo_Icon", 1, 8, Mod_Menu_Base_Name, Head_txt, 1, "Best Menu", 9, 0);
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, FALSE);*/
	}

	void notify_Custom(std::string str1, std::string str) { notify_Custom(&str1[0], &str[0]); }

	void notify_Original(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(5);
		HUD::THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(255, 255, 255, 255);
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	}

	void notify_Original(std::string str) { notify_Original(&str[0]); }

	void notify_Red(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(5);
		HUD::THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(255, 0, 0, 255);
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	}

	void notify_Red(std::string str) { notify_Red(&str[0]); }

	void notify_Green(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(5);
		HUD::THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(0, 255, 0, 255);
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	}

	void notify_Green(std::string str) { notify_Green(&str[0]); }

	char status_text[2048] = {0};

	void update_status_text()
	{
		if (GetTickCount() < 2500)
		{
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_SCALE(0.55f, 0.55f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_WRAP(0.0f, 1.0f);
			HUD::SET_TEXT_CENTRE(1);
			HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			HUD::SET_TEXT_EDGE(1, 0, 0, 0, 205);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(status_text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.5, 0);
		}
	}

	void notifyleft(char* msg)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(2000, 1);
	}

	void notifyBottom(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_PRINT(4000, 1);
	}

	void notifyBottom(std::string str) { notifyBottom(&str[0]); }

	void notifyMap(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = {0};
		sprintf_s(buff2, "%s", buf);

		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, FALSE);
	}

	void notifyMap(std::string str) { notifyMap(&str[0]); }

	void notifyCenter(char* fmt, ...)
	{
		char buf[2048] = {0};
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		sprintf_s(status_text, "%s", buf);
	}

	void notifyCenter(std::string str) { notifyCenter(&str[0]); }

	//DRAWING FUNCTIONS
	void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
	{
		GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7, 0);
	}

	void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft,
	                    float textLeft, bool active, bool title, bool rescaleText)
	{
		// default values
		int text_col[4] = {255, 255, 255, 255},
		    rect_col[4] = {0, 0, 0, 80};
		float text_scale = 0.30f;
		int font = 0;
		bool outline = true;
		bool dropshadow = true;

		// correcting values for active line
		if (active)
		{
			outline = false;
			dropshadow = true;
			text_col[0] = 0;
			text_col[1] = 0;
			text_col[2] = 0;
			text_col[3] = 255;

			rect_col[0] = 255;
			rect_col[1] = 255;
			rect_col[2] = 255;
			rect_col[3] = 80;

			if (rescaleText)text_scale = 0.30f;
		}

		if (title)
		{
			outline = true;
			dropshadow = true;
			text_col[0] = 255;
			text_col[1] = 255;
			text_col[2] = 255;
			text_col[3] = 255;

			rect_col[0] = 93;
			rect_col[1] = 182;
			rect_col[2] = 229;
			rect_col[2] = 255;

			if (rescaleText)text_scale = 0.36f;
			font = 0;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;

		float lineWidthScaled = lineWidth / static_cast<float>(screen_w); // line width
		float lineTopScaled = lineTop / static_cast<float>(screen_h); // line top offset
		float textLeftScaled = textLeft / static_cast<float>(screen_w); // text left offset
		float lineHeightScaled = lineHeight / static_cast<float>(screen_h); // line height

		float lineLeftScaled = lineLeft / static_cast<float>(screen_w);

		// this is how it's done in original scripts

		// text upper part
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_SCALE(0.0, text_scale);
		HUD::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		HUD::SET_TEXT_CENTRE(0);
		if (outline)
		{
			HUD::SET_TEXT_EDGE(1, 255, 215, 0, 255); //HUD::SET_TEXT_OUTLINE();
		}

		if (dropshadow)
		{
			HUD::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
		HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(caption.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f),
		                                   0);

		// text lower part
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_SCALE(0.0, text_scale);
		HUD::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		HUD::SET_TEXT_CENTRE(0);
		if (outline)
		{
			HUD::SET_TEXT_EDGE(1, 255, 215, 0, 255); //HUD::SET_TEXT_OUTLINE();
		}

		if (dropshadow)
		{
			HUD::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
		HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(caption.c_str());
		int num25 = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(textLeftScaled,
		                                                  (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

		// rect
		draw_rect(lineLeftScaled, lineTopScaled + 0.00278f,
		          lineWidthScaled,
		          static_cast<float>(num25) * HUD::GET_RENDERED_CHARACTER_HEIGHT(text_scale, 0) + lineHeightScaled *
		          1.0f + 0.005f,
		          rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}

	// Good Header Options

	char str[69];

	char* Add_Strings(char* string1, char* string2)
	{
		memset(str, 0, sizeof(str));
		strcpy_s(str, "");
		strcpy_s(str, string1);
		strcat_s(str, string2);
		return str;
	}
}
