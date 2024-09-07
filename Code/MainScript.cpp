#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "stdafx.h"
#include "Functions.hpp"

namespace Big
{





	enum Submenu : std::uint32_t
	{
		Home_Menu,
		Local_Menu,

		Vehicle_Menu,
		Vehicle_Spawner,
		Vehicle_Spawner_Settings,
		Vehicle_Settings,

		Protection_Main,

		Online_P_List,
		Selected_P_Menu,
		RemovalsP,
		FriendlyP,
		GriefingP,
		TeleportP,

		IPLs,
		Landmarks,
		Airports,
		Shops,
		Safehouses,

		Movement,

		Animations,
		Scenarios,
		Trails,
		HandTrailsNEW,
		Feettrails,

		Money_Menu,
		Recovery_Level,
		Recovery_Sets,
		Unlock_Recovery,
		Increase_Recovery,
		CasinoHeist,
		ContractDLC,
		Doomsday,
		CayoHeist,


		WeatherOp,
		TimeOp,

		Outfits,
		Editor,

		EventStarter,
		requestsrv,
		Online_PP_List,

		SubmenuTelepor,
		SubmenuRecovery,
		SubmenuMisc,
		SubmenuWeapon,
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		Bool_Menu
	};

	inline std::size_t DemoListPos = 0;
	inline std::size_t DemoListPos1 = 0;
	inline std::size_t DemoListPos2 = 0;
	inline std::size_t DemoListPos3 = 0;
	inline std::size_t DemoListPos4 = 0;
	inline std::size_t DemoListPos5 = 0;
	inline std::size_t DemoListPos6 = 0;
	inline std::size_t DemoListPos7 = 0;
	inline std::size_t DemoListPos8 = 0;
	inline std::size_t DemoListPos9 = 0;
	inline std::size_t DemoListPos10 = 0;
	inline std::size_t DemoListPos11 = 0;
	inline std::size_t DemoListPos12 = 0;
	inline std::size_t DemoListPos13 = 0;
	inline std::size_t DemoListPos14 = 0;
	inline std::size_t DemoListPos15 = 0;
	inline std::size_t DemoListPos16 = 0;
	inline std::size_t DemoListPos17 = 0;
	inline std::size_t DemoListPos18 = 0;
	inline std::size_t DemoListPos19 = 0;
	inline std::size_t DemoListPos20 = 0;
	inline std::size_t DemoListPos21 = 0;
	inline std::size_t DemoListPos22 = 0;
	inline std::size_t DemoListPos23 = 0;
	inline std::size_t DemoListPos24 = 0;
	inline std::size_t DemoListPos25 = 0;
	inline std::size_t DemoListPos26 = 0;
	inline std::size_t DemoListPos27 = 0;
	inline std::size_t DemoListPos28 = 0;
	inline std::size_t DemoListPos29 = 0;
	inline std::size_t DemoListPos30 = 0;
	inline std::size_t DemoListPos31 = 0;
	inline std::size_t PedIndex = 0;

	int testa = 0;
	int testb = 0;
	int testc = 0;
	int testd = 0;
	int teste = 0;
	int testf = 0;
	int testg = 0;
	int testh = 0;
	int testi = 0;
	int testj = 0;
	int testk = 0;
	int testl = 0;
	int testm = 0;
	int testn = 0;
	int testo = 0;

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void ytd_loader(const char* ytd, const char* texture) {
		// Construct the file path directly using std::string
		std::string m_file_path = std::string(R"(C:\Axelrod\Textures\)") + ytd;

		// if file does not exist, return
		if (!std::filesystem::exists(m_file_path)) {
			g_Logger->Error("Failed to find texture dictionary.");
			return;
		}

		// Register the raw file
		DWORD texture_id{};
		g_GameFunctions->m_register_raw_file(&texture_id, m_file_path.c_str(), false, ytd, false, true);

		// Check if the texture dictionary is already loaded
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture)) {
		  for (int i = 0; i < 5; ++i) {
		    GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture, false);
		    if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture)) {
		      g_Logger->Info("Found Axelrod Textures");
		      break;
		    }
		  }
		}
	}

	void MainScript::Initialize()
	{
		ytd_loader("Axelrod.ytd", "Axelrod");
		m_Initialized = true;
		using namespace UserInterface;

		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Isn't " BIGBASE_NAME " the fucking best?");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Isn't " BIGBASE_NAME " the fucking best?");

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", Home_Menu, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Self", nullptr, Local_Menu);
			sub->AddOption<SubOption>("Weapons", nullptr, SubmenuWeapon);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuTelepor);
			sub->AddOption<SubOption>("Protection", nullptr, Protection_Main);
			sub->AddOption<SubOption>("Networks", nullptr, Online_P_List);
			sub->AddOption<SubOption>("Vehicle", nullptr, Vehicle_Menu);
			sub->AddOption<SubOption>("Weather", nullptr, WeatherOp);
			sub->AddOption<SubOption>("Recovery", nullptr, SubmenuRecovery);
			sub->AddOption<SubOption>("Misc", nullptr, SubmenuMisc);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
			sub->AddOption<RegularOption>("Unload", "Unload the menu.", []
			{
				g_Running = false;
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Self", Local_Menu, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Movement", nullptr, Movement);
				sub->AddOption<SubOption>("Outfits", nullptr, Outfits);
				//sub->AddOption<SubOption>("Animations", nullptr, Animations);
				sub->AddOption<SubOption>("Scenarios", nullptr, Scenarios);
				sub->AddOption<SubOption>("Trails", nullptr, Trails);
				sub->AddOption<BoolOption<>>("God mode", "God mode", &Godmode, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<>>("Invisible", "WHERE HE GO", &Invisible, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<>>("Fire Breath", "LOOK IM CHARIZARD", &FireBreath, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<>>("Never Wanted", "FUCK 12", &NeverWanted, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<>>("No RagDoll", "I CAN'T FALL OVER", &noragdoll, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("Super Jump", "JUMPPER", &SuperJump, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("Ultra Jump", "MY VERTICAL CRAZY", &Extremejump, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("Super Run", "RUN FOREST RUN", &Fastrun, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("Slide Run", "YOU GOT ICY FEET", &SlideRun, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("NoClip", "IM FLYING HIGH", &NoClip, BoolDisplay::OnOff);
				sub->AddOption<RegularOption>("Max Health", "STIM SHOTS", [] { PED::SET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID())); });
				sub->AddOption<RegularOption>("Armor", "ARMOR PLATES", [] { PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID())); });
				sub->AddOption<RegularOption>("Suicide", "FUCKING KILL YOURSELF", [] {PED::SET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), NULL); });
				sub->AddOption<RegularOption>("Clean", nullptr, [] { PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID()); });
				sub->AddOption<RegularOption>("Dry", nullptr, [] { PED::CLEAR_PED_WETNESS(PLAYER::PLAYER_PED_ID()); });
				sub->AddOption<RegularOption>("5 Star Wanted", "5 STARS WANTED", [] { MISC::SET_FAKE_WANTED_LEVEL(5); });
				sub->AddOption<RegularOption>("Clear 5 Star Wanted", "POOF THEY GONE", [] { MISC::SET_FAKE_WANTED_LEVEL(0); });
				sub->AddOption<RegularOption>("Clone Ped", "THEY CLONING ME NOW", [] { PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 1, 1, 1); });
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Trails", Trails, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Hand Trails", nullptr, HandTrailsNEW);
				sub->AddOption<SubOption>("Feet Trails", nullptr, Feettrails);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Hand", HandTrailsNEW, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>("Hand Trails", nullptr, &HandTrails, BoolDisplay::OnOff);
				sub->AddOption<NumberOption<float>>(("R"), nullptr, &handred, 0, 255, 1, 0, true, "", "", [] {});
				sub->AddOption<NumberOption<float>>(("G"), nullptr, &handgreen, 0, 255, 1, 0, true, "", "", [] {});
				sub->AddOption<NumberOption<float>>(("B"), nullptr, &handblue, 0, 255, 1, 0, true, "", "", [] {});
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Feet", Feettrails, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>("Feet Trails", nullptr, &FootTrails, BoolDisplay::OnOff);
				sub->AddOption<NumberOption<float>>(("R"), nullptr, &footred, 0, 255, 1, 0, true, "", "", [] {});
				sub->AddOption<NumberOption<float>>(("G"), nullptr, &footgreen, 0, 255, 1, 0, true, "", "", [] {});
				sub->AddOption<NumberOption<float>>(("B"), nullptr, &footblue, 0, 255, 1, 0, true, "", "", [] {});
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Outfits", Outfits, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Outfit Editor", nullptr, Editor);
				//sub->AddOption<RegularOption>("Load Outfit", "LOAD YOUR OUTFIT", [] { Outfit(0); });
				sub->AddOption<RegularOption>("Random Outfit", "RANDOM OUTFITS", [] { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); });
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Outfits Editor", Editor, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<std::int32_t>>("Face", nullptr, &testa, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Head", nullptr, &testb, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Hair", nullptr, &testc, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Torso", nullptr, &testd, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Legs", nullptr, &teste, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Hands", nullptr, &testf, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Feet", nullptr, &testg, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Eyes", nullptr, &testh, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Accessories", nullptr, &testi, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Tasks", nullptr, &testj, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Textures", nullptr, &testk, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Torso2", nullptr, &testl, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Head Props", nullptr, &testm, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, testm, 0, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Eye Props", nullptr, &testn, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, testn, 0, 0, 0); });
				sub->AddOption<NumberOption<std::int32_t>>("Ear Props", nullptr, &testo, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, testo, 0, 0, 0); });
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Scenarios", Scenarios, [](RegularSubmenu* sub)
			{
				sub->AddOption<RegularOption>("Stop All Scenarios", nullptr, [] { TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID()); });
				sub->AddOption<RegularOption>("Paparazzi", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, true); });
				sub->AddOption<RegularOption>("Drug Dealer", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true); });
				sub->AddOption<RegularOption>("Drinking Coffee", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, true); });
				sub->AddOption<RegularOption>("Playing Instruments", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, true); });
				sub->AddOption<RegularOption>("Flexing", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, true); });
				sub->AddOption<RegularOption>("Jogging", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, true); });
				sub->AddOption<RegularOption>("Binoculars", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, true); });
				sub->AddOption<RegularOption>("Clipboard", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, true); });
				sub->AddOption<RegularOption>("Bench Press", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true); });
				sub->AddOption<RegularOption>("Chin Ups", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true); });
				sub->AddOption<RegularOption>("BBQ", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, true); });
				sub->AddOption<RegularOption>("Superhero", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, true); });
				sub->AddOption<RegularOption>("Fishing", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, true); });
				sub->AddOption<RegularOption>("Drilling", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, true); });
				sub->AddOption<RegularOption>("Tennis", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, true); });
				sub->AddOption<RegularOption>("Hammering", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, true); });
				sub->AddOption<RegularOption>("Smoking Pot", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, true); });
				sub->AddOption<RegularOption>("Welding", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, true); });
				sub->AddOption<RegularOption>("Gold Player", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, true); });
				sub->AddOption<RegularOption>("Drinking", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, true); });
				sub->AddOption<RegularOption>("Idle Cop", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, true); });
				sub->AddOption<RegularOption>("Film Shocking", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true); });
				sub->AddOption<RegularOption>("Leaf Blower", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true); });
				sub->AddOption<RegularOption>("Security", nullptr, [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true); });

			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
			sub->AddOption<SubOption>("Info bar", nullptr, SubmenuSettingsSubmenuBar);
			sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
			sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
			sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
			sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
			sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Width", nullptr, &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_UiManager->m_Sounds, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<std::atomic_bool>>("Log Window", nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Info bar", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
			{
				g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			});

			switch (g_UiManager->m_HeaderType)
			{
			case HeaderType::Static:
				sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
				break;
			case HeaderType::Gradient:
				sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
				break;
			default: ;
			}

			sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_UiManager->m_HeaderGradientTransparent, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_UiManager->m_HeaderGradientFlip, BoolDisplay::YesNo);

			sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_UiManager->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_UiManager->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_UiManager->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_UiManager->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Size", nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_UiManager->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
 3);
			sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_UiManager->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_UiManager->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Players", Online_PP_List, [](RegularSubmenu* sub)
		{
			for (Player i = 0; i < 31; ++i)
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
				{
					sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, Selected_P_Menu, [=]
					{
						g_SelectedPlayer = i;
					});
				}
			}
		});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, Selected_P_Menu, [](PlayerSubmenu* sub)
		{
			sub;
		});
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		FunctionsOnTick();
		g_UiManager->OnTick();
	}
}
