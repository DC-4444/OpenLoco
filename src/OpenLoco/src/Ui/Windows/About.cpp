#include "Graphics/Colour.h"
#include "Graphics/Gfx.h"
#include "Graphics/ImageIds.h"
#include "Graphics/SoftwareDrawingEngine.h"
#include "Graphics/TextRenderer.h"
#include "Localisation/StringIds.h"
#include "Objects/InterfaceSkinObject.h"
#include "Objects/ObjectManager.h"
#include "Ui/Widget.h"
#include "Ui/Widgets/ButtonWidget.h"
#include "Ui/Widgets/CaptionWidget.h"
#include "Ui/Widgets/FrameWidget.h"
#include "Ui/Widgets/ImageButtonWidget.h"
#include "Ui/Widgets/PanelWidget.h"
#include "Ui/WindowManager.h"

namespace OpenLoco::Ui::Windows::About
{
    static constexpr Ui::Size32 kWindowSize = { 400, 260 };

    namespace widx
    {
        enum
        {
            frame,
            title,
            close,
            panel,
            music_acknowledgements_btn,
        };
    }

    static constexpr auto _widgets = makeWidgets(
        Widgets::Frame({ 0, 0 }, kWindowSize, WindowColour::primary),
        Widgets::Caption({ 1, 1 }, { kWindowSize.width - 2, 13 }, Widgets::Caption::Style::whiteText, WindowColour::primary, StringIds::about_locomotion_caption),
        Widgets::ImageButton({ kWindowSize.width - 15, 2 }, { 13, 13 }, WindowColour::primary, ImageIds::close_button, StringIds::tooltip_close_window),
        Widgets::Panel({ 0, 15 }, { kWindowSize.width, 245 }, WindowColour::secondary),
        Widgets::Button({ 100, 234 }, { kWindowSize.width / 2, 12 }, WindowColour::secondary, StringIds::music_acknowledgements_btn));

    static const WindowEventList& getEvents();

    // 0x0043B26C
    void open()
    {
        if (WindowManager::bringToFront(WindowType::about) != nullptr)
        {
            return;
        }

        auto window = WindowManager::createWindowCentred(
            WindowType::about,
            kWindowSize,
            WindowFlags::none,
            getEvents());

        window->setWidgets(_widgets);
        window->initScrollWidgets();

        const auto interface = ObjectManager::get<InterfaceSkinObject>();
        window->setColour(WindowColour::primary, interface->windowTitlebarColour);
        window->setColour(WindowColour::secondary, interface->windowOptionsColour);
    }

    // 0x0043B4AF
    static void onMouseUp(Ui::Window& window, const WidgetIndex_t widgetIndex, [[maybe_unused]] const WidgetId id)
    {
        switch (widgetIndex)
        {
            case widx::close:
                WindowManager::close(window.type);
                break;

            case widx::music_acknowledgements_btn:
                AboutMusic::open();
                break;
        }
    }

    // 0x0043B2E4
    static void draw(Ui::Window& window, Gfx::DrawingContext& drawingCtx)
    {
        auto tr = Gfx::TextRenderer(drawingCtx);

        // Draw widgets.
        window.draw(drawingCtx);

        auto point = Point(window.x + kWindowSize.width / 2, window.y + 25);

        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_69);

        point.y += 10;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_70);

        // Chris Sawyer logo
        drawingCtx.drawImage(window.x + 92, window.y + 52, ImageIds::chris_sawyer_logo_small);

        point.y += 79;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_71);

        point.y += 10;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_72);

        point.y += 10;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_73);

        point.y += 10;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_74);

        point.y += 13;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_75);

        point.y += 25;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_76);

        point.y += 10;
        tr.drawStringCentred(point, Colour::black, StringIds::about_locomotion_77);

        // Licenced to Atari
        point.y += 25;
        tr.drawStringCentred(point, Colour::black, StringIds::licenced_to_atari_inc);
    }

    static constexpr WindowEventList kEvents = {
        .onMouseUp = onMouseUp,
        .draw = draw,
    };

    static const WindowEventList& getEvents()
    {
        return kEvents;
    }
}
