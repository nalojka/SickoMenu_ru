#include "pch-il2cpp.h"
#include "menu.hpp"
#include "imgui/imgui.h"
#include "tabs/about_tab.h"
#include "tabs/doors_tab.h"
#include "tabs/game_tab.h"
#include "tabs/host_tab.h"
#include "tabs/players_tab.h"
#include "tabs/radar_tab.h"
#include "tabs/replay_tab.h"
#include "tabs/esp_tab.h"
#include "tabs/sabotage_tab.h"
#include "tabs/self_tab.h"
#include "tabs/settings_tab.h"
#include "tabs/tasks_tab.h"
#ifdef _DEBUG
#include "tabs/debug_tab.h"
#endif
#include "state.hpp"
#include "gui-helpers.hpp"
#include <map>
#include <vector>
#include <string>

namespace Menu {
	static bool openAbout = false;
	static bool openSettings = false;
	static bool openGame = false;
	static bool openSelf = false;
	static bool openRadar = false;
	static bool openReplay = false;
	static bool openEsp = false;
	static bool openPlayers = false;
	static bool openTasks = false;
	static bool openSabotage = false;
	static bool openDoors = false;
	static bool openHost = false;
#ifdef _DEBUG
	static bool openDebug = false;
#endif
	static std::string searchQuery = (std::string)"";

	std::map<std::string, std::vector<std::string>> categories = {
		{"Настройки", {"Показать бинды", "Разрешить бинды в чате", "Показывать меню при запуске", "Отключить SickoMenu",
              "Название конфига", "Загрузить конфиг", "Сохранить конфиг", "Масштабирование под DPI", "Размер меню", 
              "Цвет темы", "Градиентная тема", "Подогнать фон под тему", "Радужная тема", "Сбросить тему", 
              "Прозрачность", "Показать меню отладки", "Никнейм", "Установить ник аккаунта", "Автоник", 
              "Кастомный код", "Скрыть код лобби", "RGB код лобби", "Разблокировать косметику", "Безопасный режим", 
              "Показывать другим использование SickoMenu", "Фейк гостевого аккаунта", "Кастомный гостевой код", 
              "Фейк уровня", "Фейк платформы", "Отключить античит хоста (+25 Mode)", "FPS"}},

		{"Игра", {"Множитель скорости", "Дистанция убийства", "Без кулдауна способностей", "Умножить скорость", 
				"Изменять дистанцию убийства", "Случайный цвет", "Установить цвет", "Снайперский цвет", "Консоль", 
				"Сбросить внешность", "Убить всех", "Защитить всех", "Отключить вентиляцию", "Спам репортами", 
				"Убить всех мирных", "Убить всех предателей", "Выкинуть всех из вент", "Сообщение в чат", "Отправить", 
				"Отправить в AUM", "Спам", "Шаблоны чата", "Попытка краша", "Перегрузить всех", "Лаггировать всех", 
				"Включить античит (SMAC)", "Белый список", "Черный список"}},

		{"Персонаж", {"Макс. видимость", "Сквозь стены", "Отключить HUD", "Свободная камера", "Зум", 
					"Всегда показывать кнопку чата", "Разрешить Ctrl+C/V в чате", "Читать сообщения призраков", 
					"Читать/отправлять SickoChat", "Кастомное имя", "Кастомное имя для всех", "Серверное кастомное имя", 
					"Показывать роли", "Сокращать роли", "Цветные точки у ников", "Показывать инфо в лобби", 
					"Показывать голоса", "Видеть призраков", "Видеть защиты", "Видеть кулдаун убийства", 
					"Отключить анимацию убийства", "Темный режим", "Показывать хоста", "Скрыть водяной знак", 
					"Показывать голосования", "Показывать FPS", "Открыть венты", "Двигаться в вентах/трансформации", 
					"Постоянное движение", "Без анимации трансформации", "Копировать код лобби при отключении", "Ноклип", 
					"Разрешить убийства в лобби", "Убивать других предателей", "Бесконечная дистанция убийства", 
					"Обходить защиту ангела", "Автоубийство", "Выполнять задания как предатель", "Фейк жизни", 
					"Бессмертие", "Телепортация", "Вращать всех", "Выбрать роль", "Установить роль", 
					"Установить фейк-роль", "Автоустановка фейк-роли", "Показывать инфо лобби", "Видеть фантомов", 
					"Репортить тело после убийства", "Предотвращать саморепорт", "Циклер", "Циклить во время собрания", 
					"Циклить между игроками", "Конфьюзер (случайная внешность)"}},

		{"Радар", {"Показывать радар", "Показывать тела", "Показывать призраков", "ПКМ для телепорта", 
				"Скрывать радар на собраниях", "Отображать иконки", "Фиксировать позицию радара", "Показывать границу"}},

		{"Повтор", {"Показывать повтор", "Показывать только последние секунды", "Очищать после собрания"}},

		{"ESP", {"Включить", "Показывать призраков", "Скрывать на собраниях", "Показывать рамки", 
				"Показывать линии", "Показывать расстояния", "По ролям"}},

		{"Игроки", {"Игроки"}},

		{"Задания", {"Выполнить все задания", "Проиграть анимацию сканирования"}},

		{"Саботажи", {"Отключить саботажи", "Автопочинка саботажей", "Починить саботаж", "Саботировать всё", 
					"Случайный саботаж", "Саботаж света", "Саботаж реактора", "Саботаж кислорода", 
					"Саботаж связи", "Отключить свет", "Активировать грибной хаос"}},

		{"Двери", {"Закрыть все двери", "Закрыть дверь комнаты", "Заблокировать все двери", 
				"Разблокировать все двери", "Автооткрытие дверей"}},

		{"Хост", {"Кастомное число предателей", "Количество предателей", "Принудительный старт игры", 
				"Отключить собрания", "Отключить саботажи", "Отключить конец игры", "Завершить игру", 
				"Принудительный цвет для всех", "Принудительное имя для всех", "Спам подвижной платформой", 
				"Разблокировать кнопку убийства", "Разрешить убийства в лобби", "Убивать будучи невидимым", 
				"Режим игры", "Показывать таймер лобби", "Автостарт игры", "Режим наблюдателя"}},

		{"Отладка", {"Включить окклюзию", "Принудительная загрузка настроек", "Принудительное сохранение настроек", 
					"Очистка RPC очередей", "Логировать Unity-дебаг", "Логировать хуки", "Цвета", 
					"Профайлер", "Эксперименты", "Включить античит (SMAC)", "Система очков (только для хоста)"}}
#endif
				   // Add more settings here as needed
	};

	void CloseAllOtherTabs(Tabs openTab) {
		openAbout = openTab == Tabs::About;
		openSettings = openTab == Tabs::Settings;
		openGame = openTab == Tabs::Game;
		openSelf = openTab == Tabs::Self;
		openRadar = openTab == Tabs::Radar;
		openReplay = openTab == Tabs::Replay;
		openEsp = openTab == Tabs::Esp;
		openPlayers = openTab == Tabs::Players;
		openTasks = openTab == Tabs::Tasks;
		openSabotage = openTab == Tabs::Sabotage;
		openDoors = openTab == Tabs::Doors;
		openHost = openTab == Tabs::Host;
#ifdef _DEBUG
		openDebug = openTab == Tabs::Debug;
#endif
	}

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(600, 450) * State.dpiScale, ImGuiCond_None);
		ImGui::SetNextWindowBgAlpha(State.MenuThemeColor.w);
	}

	bool init = false;
	bool firstRender = true;
	bool isPanicWarning = false;

	std::string ToLower(const std::string& str) {
		std::string lowerStr = str;
		std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}

	static std::string StrRev(std::string str) {
		std::string new_str = str;
		std::reverse(new_str.begin(), new_str.end());
		return new_str;
	}

	void RenderSearchResults() {
		if (searchQuery.size() == 0) return;

		std::string lowerQuery = ToLower(searchQuery);

		std::vector<std::string> searchResults = {};

		for (const auto& category : categories) {
			for (const auto& setting : category.second) {
				if (ToLower(setting).find(lowerQuery) != std::string::npos) {
					searchResults.push_back(category.first);
					break;
				}
			}
		}
		ImGui::TextColored(ImVec4(0.f, 0.f, 0.f, 0.f), "space");
		if (searchResults.size() == 0) BoldText("No results.");
		else {
			BoldText(("Search Result" + std::string(searchResults.size() == 1 ? "" : "s")).c_str());
			for (std::string i : searchResults) {
				ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.f), i.c_str());
			}
		}
	}

	void Render() {
		try {
			if (!init)
				Menu::Init();
			std::string modText = std::format("SickoMenu {}", State.SickoVersion);
			ImGui::Begin("SickoMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse);
			static ImVec4 titleCol = State.MenuThemeColor;
			if (State.RgbMenuTheme)
				titleCol = State.RgbColor;
			else
				titleCol = State.GradientMenuTheme ? State.MenuGradientColor : State.MenuThemeColor;
			titleCol.w = 1.f;
			ImGui::TextColored(titleCol, modText.c_str());
			ImVec4 DiddyCol = ImVec4(0.79f, 0.03f, 1.f, 1.f);
			if (State.AprilFoolsMode) {
				ImGui::SameLine(0.f, 0.f);
				if (State.DiddyPartyMode) ImGui::TextColored(DiddyCol, " [Diddy Party Mode]");
				else ImGui::TextColored(DiddyCol, IsChatCensored() || IsStreamerMode() ? " [F***son Mode]" : " [Fuckson Mode]");
			}
			ImGui::SameLine(ImGui::GetWindowWidth() - 19 * State.dpiScale);
			if (AnimatedButton("-")) State.ShowMenu = false; //minimize button
			//ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);
			ImGui::BeginChild("###SickoMenu", ImVec2(90 * State.dpiScale, 0), true, ImGuiWindowFlags_NoBackground);
			// Search field
			ImGui::SetNextItemWidth(90 * State.dpiScale); // Adjust the width of the input box
			if (InputStringWithHint("##Search", "Search...", &searchQuery) && State.AprilFoolsMode) {
				if (ToLower(searchQuery) == StrRev("nosduh")) {
					State.AprilFoolsMode = !State.AprilFoolsMode;
					if (!State.AprilFoolsMode) State.DiddyPartyMode = false;
				}
				if (ToLower(searchQuery) == StrRev("yddid")) {
					State.DiddyPartyMode = !State.DiddyPartyMode;
				}
			}
			if (ImGui::Selectable("About", openAbout)) {
				CloseAllOtherTabs(Tabs::About);
			}
			if (ImGui::Selectable("Settings", openSettings)) {
				CloseAllOtherTabs(Tabs::Settings);
			}
			if (ImGui::Selectable("Game", openGame)) {
				CloseAllOtherTabs(Tabs::Game);
			}
			if (ImGui::Selectable("Self", openSelf)) {
				CloseAllOtherTabs(Tabs::Self);
			}
			if (ImGui::Selectable("Radar", openRadar)) {
				CloseAllOtherTabs(Tabs::Radar);
			}
			if (ImGui::Selectable("Replay", openReplay)) {
				CloseAllOtherTabs(Tabs::Replay);
			}
			if (ImGui::Selectable("ESP", openEsp)) {
				CloseAllOtherTabs(Tabs::Esp);
			}
			if ((IsInGame() || IsInLobby()) && ImGui::Selectable("Players", openPlayers)) {
				CloseAllOtherTabs(Tabs::Players);
			}
			if ((IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL) && ImGui::Selectable("Tasks", openTasks)) {
				CloseAllOtherTabs(Tabs::Tasks);
			}
			if (IsInGame() && ShipStatus__TypeInfo->static_fields->Instance != NULL && ImGui::Selectable("Sabotage", openSabotage)) {
				CloseAllOtherTabs(Tabs::Sabotage);
			}
			if ((IsInGame() && !State.mapDoors.empty()) && ImGui::Selectable("Doors", openDoors)) {
				CloseAllOtherTabs(Tabs::Doors);
			}
			if (IsHost() && ImGui::Selectable("Host", openHost)) {
				CloseAllOtherTabs(Tabs::Host);
			}
#ifdef _DEBUG
			if (State.showDebugTab && ImGui::Selectable("Debug", openDebug)) {
				CloseAllOtherTabs(Tabs::Debug);
			}
#endif
			RenderSearchResults();

			ImVec4 PanicCol = ImVec4(1.f, 0.f, 0.f, 1.f);
			ImVec4 GreenCol = ImVec4(0.f, 1.f, 0.f, 1.f);
			if (!isPanicWarning) {
				ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 90 * State.dpiScale, ImGui::GetWindowHeight() - 20 * State.dpiScale));
				if (!State.AprilFoolsMode && ColoredButton(PanicCol, "Disable Menu")) {
					isPanicWarning = State.PanicWarning;
					if (!State.PanicWarning) State.PanicMode = true;
				}
				if (State.AprilFoolsMode && ColoredButton(DiddyCol,State.DiddyPartyMode ? "Rizz Up Diddy" : 
						StrRev(std::format("nosduH {}F", IsChatCensored() || IsStreamerMode() ? "***" : "kcu")).c_str())) {
					isPanicWarning = State.PanicWarning;
					if (!State.PanicWarning) State.PanicMode = true;
				}
			}
			else {
				bool panicKeybind = State.KeyBinds.Toggle_Sicko != 0x00;
				ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 90 * State.dpiScale,
					ImGui::GetWindowHeight() - 65 * State.dpiScale));
				if (!panicKeybind) {
					ImGui::TextColored(PanicCol, "No Panic");
					ImGui::TextColored(PanicCol, "Keybind!");
				}
				else {
					ImGui::TextColored(PanicCol, ("Press " + (std::string)KeyBinds::ToString(State.KeyBinds.Toggle_Sicko)).c_str());
					ImGui::TextColored(PanicCol, ("to re-enable!"));
				}
				ImGui::TextColored(PanicCol, "Continue?");
				if (ColoredButton(PanicCol, "Yes")) {
					isPanicWarning = false;
					State.PanicMode = true;
				}
				ImGui::SameLine();
				if (ColoredButton(GreenCol, "No")) {
					isPanicWarning = false;
				}
			}

			if (firstRender) {
				firstRender = false;
				CloseAllOtherTabs(Tabs::About); //welcome the user on startup
			}
			//ImGui::EndTabBar();
			ImGui::EndChild();

			//open respective tabs
			if (openAbout) AboutTab::Render();
			else {
				if (!State.HasOpenedMenuBefore) State.HasOpenedMenuBefore = true;
			}
			if (openSettings) SettingsTab::Render();
			if (openGame) GameTab::Render();
			if (openSelf) SelfTab::Render();
			if (openRadar) RadarTab::Render();
			if (openReplay) ReplayTab::Render();
			if (openEsp) EspTab::Render();
			if (openPlayers) {
				if (IsInGame() || IsInLobby()) PlayersTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
			if (openTasks) {
				if (IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL) TasksTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
			if (openSabotage) {
				if (IsInGame()) SabotageTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
			if (openDoors) {
				if (IsInGame() && !State.mapDoors.empty()) DoorsTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
			if (openHost) {
				if (IsHost()) HostTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
#ifdef _DEBUG
			if (openDebug) {
				if (State.showDebugTab) DebugTab::Render();
				else {
					CloseAllOtherTabs(Tabs::Game);
					GameTab::Render();
				}
			}
#endif

			ImGui::End();
		}
		catch (...) {
			LOG_ERROR("Exception occurred when rendering menu");
		}
	}
}
