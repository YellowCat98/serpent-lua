#include <SerpentLua.hpp>

using namespace geode::prelude;

void SerpentLua::bindings::_geode::bind(sol::state& lua) {
    lua.new_usertype<Notification>("Notification",
        sol::no_constructor,
        "create", sol::overload(
            [](const std::string& text, NotificationIcon icon, float time) {
                return Notification::create(text, icon, time);
            },
            [](const std::string& text, NotificationIcon icon) {
                return Notification::create(text, icon, geode::NOTIFICATION_DEFAULT_TIME);
            },
            [](const std::string& text) {
                return Notification::create(text, NotificationIcon::None, geode::NOTIFICATION_DEFAULT_TIME);
            }
        ),
        "show", &Notification::show,
        "cancel", &Notification::cancel,
        "hide", &Notification::hide
    );

    lua.set_function("createQuickPopup", 
        [](const char* title, const std::string& content, const char* btn1, const char* btn2, sol::function selected) {
            return geode::createQuickPopup(title, content, btn1, btn2, [=](FLAlertLayer* layer, bool pressed) {
                selected(layer, pressed);
            });
        }
    );

    lua.new_usertype<BaseSeedValue>("BaseSeedValue",
        sol::call_constructor, sol::constructors<BaseSeedValue()>()
    );

    lua.new_usertype<SeedValueRSV>("SeedValueRSV",
        sol::base_classes, sol::bases<BaseSeedValue>(),
        "value", sol::resolve<int()>(&SeedValueRSV::value)
    );
}

void SerpentLua::bindings::_geode::enums(sol::state& lua) {
    lua.new_enum<NotificationIcon>("NotificationIcon", {
        {"None", NotificationIcon::None},
        {"Loading", NotificationIcon::Loading},
        {"Success", NotificationIcon::Success},
        {"Warning", NotificationIcon::Warning},
        {"Error", NotificationIcon::Error},
        {"Info", NotificationIcon::Info}
    });
}

void SerpentLua::bindings::cocos::bind(sol::state& lua) {
    lua.new_usertype<CCObject>("CCObject",
        "release", &CCObject::release,
        "retain", &CCObject::retain,
        "copy", &CCObject::copy,
        "autorelease", &CCObject::autorelease,
        "getTag", &CCObject::getTag,
        "setTag", &CCObject::setTag,
        "setObjType", &CCObject::setObjType,
        "isEqual", &CCObject::isEqual
    );

    lua.new_usertype<CCPoint>("CCPoint",
        sol::constructors<CCPoint(float, float)>(),
        "x", &CCPoint::x,
        "y", &CCPoint::y
    );

    lua.new_usertype<CCSize>("CCSize",
        sol::constructors<CCSize(float, float)>(),
        "height", &CCSize::height,
        "width", &CCSize::width
    );

    lua.new_usertype<CCRect>("CCRect",
        "origin", &CCRect::origin,
        "size", &CCRect::size,
        "intersectsRect", sol::overload(&CCRect::intersectsRect)
    );

    lua.new_usertype<ccColor3B>("ccColor3B",
        sol::constructors<ccColor3B()>(),
        "r", &ccColor3B::r,
        "g", &ccColor3B::g,
        "b", &ccColor3B::b
    );

    lua.new_usertype<ccColor4B>("ccColor4B",
        sol::constructors<ccColor4B()>(),
        "r", &ccColor4B::r,
        "g", &ccColor4B::g,
        "b", &ccColor4B::b,
        "a", &ccColor4B::a
    );

    lua.new_usertype<CCDirector>("CCDirector",
        "get", &CCDirector::get,
        "getWinSize", &CCDirector::getWinSize,
        "replaceScene", &CCDirector::replaceScene,
        "pushScene", &CCDirector::pushScene,
        "popScene", &CCDirector::popScene
    );

    lua.new_usertype<CCNode>("CCNode", sol::base_classes, sol::bases<CCObject>(),
        "create", &CCNode::create,
        "init", &CCNode::init,
        "description", &CCNode::description,
        "setZOrder", &CCNode::setZOrder,
        "getZOrder", &CCNode::getZOrder,
        "setVertexZ", &CCNode::setVertexZ,
        "getVertexZ", &CCNode::getVertexZ,
        "setScaleX", &CCNode::setScaleX,
        "getScaleY", &CCNode::getScaleY,
        "setScale", sol::overload(
            static_cast<void (CCNode::*)(float, float)>(&CCNode::setScale),
            static_cast<void (CCNode::*)(float)>(&CCNode::setScale)
        ),
        "setPosition", sol::overload(
            static_cast<void (CCNode::*)(float, float)>(&CCNode::setPosition),
            static_cast<void (CCNode::*)(const CCPoint&)>(&CCNode::setPosition)
        ),
        "getPosition", sol::overload(
            static_cast<const CCPoint& (CCNode::*)()>(&CCNode::getPosition)
        ),
        "setPositionX", &CCNode::setPositionX,
        "getPositionX", &CCNode::getPositionX,
        "setPositionY", &CCNode::setPositionY,
        "getPositionY", &CCNode::getPositionY,
        "setSkewX", &CCNode::setSkewX,
        "getSkewX", &CCNode::getSkewX,
        "setSkewY", &CCNode::setSkewY,
        "getSkewY", &CCNode::getSkewY,
        "setAnchorPoint", &CCNode::setAnchorPoint,
        "getAnchorPoint", &CCNode::getAnchorPoint,
        "getAnchorPointInPoints", &CCNode::getAnchorPointInPoints,
        "setContentSize", &CCNode::setContentSize,
        "getContentSize", &CCNode::getContentSize,
        "getScaledContentSize", &CCNode::getScaledContentSize,
        "setVisible", &CCNode::setVisible,
        "isVisible", &CCNode::isVisible,
        "setRotation", &CCNode::setRotation,
        "getRotation", &CCNode::getRotation,
        "setRotationX", &CCNode::setRotationX,
        "getRotationX", &CCNode::getRotationX,
        "setRotationY", &CCNode::setRotationY,
        "getRotationY", &CCNode::getRotationY,
        "addChild", sol::overload(
            static_cast<void (CCNode::*)(CCNode*)>(&CCNode::addChild),
            static_cast<void (CCNode::*)(CCNode*, int)>(&CCNode::addChild),
            static_cast<void (CCNode::*)(CCNode*, int, int)>(&CCNode::addChild)
        ),
        "getChildByTag", sol::overload(&CCNode::getChildByTag),
        "getParent", &CCNode::getParent,
        "removeFromParent", &CCNode::removeFromParent,
        "removeFromParentAndCleanup", &CCNode::removeFromParentAndCleanup,
        "removeChild", sol::overload(
            static_cast<void (CCNode::*)(CCNode*, bool)>(&CCNode::removeChild)
        ),
        "removeChildByTag", sol::overload(
            static_cast<void (CCNode::*)(int, bool)>(&CCNode::removeChildByTag)
        ),
        "removeAllChildren", &CCNode::removeAllChildren,
        "getID", &CCNode::getID,
        "setID", sol::overload(
            static_cast<void (CCNode::*)(std::string&&)>(&CCNode::setID)
        ),
        "getChildByID", &CCNode::getChildByID,
        "getChildByIDRecursive", &CCNode::getChildByIDRecursive,
        "removeChildByID", &CCNode::removeChildByID
    );

    lua.new_usertype<CCScene>("CCScene",
        sol::base_classes, sol::bases<CCNode>(),
        "create", &CCScene::create,
        "init", &CCScene::init,
        "get", &CCScene::get
    );

    lua.new_usertype<CCRGBAProtocol>("CCRGBAProtocol",
        "setColor", sol::overload(
            static_cast<void (CCRGBAProtocol::*)(const ccColor4B&)>(&CCRGBAProtocol::setColor)
        ),
        "getColor", &CCRGBAProtocol::getColor,
        "getDisplayedColor", &CCRGBAProtocol::getDisplayedColor,
        "setOpacity", &CCRGBAProtocol::setOpacity,
        "getOpacity", &CCRGBAProtocol::getOpacity
    );

    lua.new_usertype<CCLayer>("CCLayer", sol::base_classes, sol::bases<CCNode>(),
        "create", &CCLayer::create,
        "init", &CCLayer::init
    );

    lua.new_usertype<CCLayerRGBA>("CCLayerRGBA", sol::base_classes, sol::bases<CCLayer, CCRGBAProtocol>(),
        "create", &CCLayerRGBA::create
    );

    lua.new_usertype<CCNodeRGBA>("CCNodeRGBA", sol::base_classes, sol::bases<CCNode, CCRGBAProtocol>(),
        "create", &CCNodeRGBA::create
    );

    lua.new_usertype<CCTexture2D>("CCTexture2D",
        sol::constructors<CCTexture2D()>(),
        "initWithData", &cocos2d::CCTexture2D::initWithData,
        "initWithETCFile", &cocos2d::CCTexture2D::initWithETCFile,
        "initWithImage", &cocos2d::CCTexture2D::initWithImage,
        "initWithPVRFile", &cocos2d::CCTexture2D::initWithPVRFile,
        "initWithString", sol::overload(
            static_cast<bool (CCTexture2D::*)(const char*, const char*, float)>(&cocos2d::CCTexture2D::initWithString)
        ),
        "setAliasTexParameters", &cocos2d::CCTexture2D::setAliasTexParameters,
        "setTexParameters", &cocos2d::CCTexture2D::setTexParameters,
        "releaseGLTexture", &cocos2d::CCTexture2D::releaseGLTexture
    );
}

void SerpentLua::bindings::cocos::enums(sol::state& lua) {
    lua.new_enum<CCObjectType>("CCObjectType", {
        {"PlayLayer", CCObjectType::PlayLayer},
        {"LevelEditorLayer", CCObjectType::LevelEditorLayer},
        {"GameObject", CCObjectType::GameObject},
        {"MenuLayer", CCObjectType::MenuLayer}
    });
}

void SerpentLua::bindings::robtop::bind(sol::state& lua) {
    lua.new_usertype<GooglePlayDelegate>("GooglePlayDelegate",
        "googlePlaySignedIn", &GooglePlayDelegate::googlePlaySignedIn
    );

    lua.new_usertype<MenuLayer>("MenuLayer",
        "scene", &MenuLayer::scene,
        "init", &MenuLayer::init,
        "onMoreGames", &MenuLayer::onMoreGames,
        "endGame", &MenuLayer::endGame,
        "firstNetworkTest", &MenuLayer::firstNetworkTest,
        "onAchievements", &MenuLayer::onAchievements,
        "onCreator", &MenuLayer::onCreator,
        "onDaily", &MenuLayer::onDaily,
        "onGarage", &MenuLayer::onGarage,
        "onMyProfile", &MenuLayer::onMyProfile,
        "onOptions", &MenuLayer::onOptions,
        "onOptionsInstant", &MenuLayer::onOptionsInstant,
        "onPlay", &MenuLayer::onPlay,
        "onQuit", &MenuLayer::onQuit,
        "onRobTop", &MenuLayer::onRobTop,
        "onStats", &MenuLayer::onStats,
        "openOptions", &MenuLayer::openOptions,
        "showTOS", &MenuLayer::showTOS,
        "updateUserProfileButton", &MenuLayer::updateUserProfileButton,
        "willClose", &MenuLayer::willClose
    );

    lua.new_usertype<LoadingLayer>("LoadingLayer",
        "getLoadingString", &LoadingLayer::getLoadingString,
        "init", &LoadingLayer::init,
        "loadAssets", &LoadingLayer::loadAssets,
        "scene", &LoadingLayer::scene,
        "updateProgress", &LoadingLayer::updateProgress,
        "m_unknown", &LoadingLayer::m_unknown,
        "m_unknown2", &LoadingLayer::m_unknown2,
        "m_loadStep", &LoadingLayer::m_loadStep,
        "m_caption", &LoadingLayer::m_caption,
        "m_textArea", &LoadingLayer::m_textArea,
        "m_sliderBar", &LoadingLayer::m_sliderBar,
        "m_sliderGrooveXPos", &LoadingLayer::m_sliderGrooveXPos,
        "m_sliderGrooveHeight", &LoadingLayer::m_sliderGrooveHeight,
        "m_fromRefresh", &LoadingLayer::m_fromRefresh
    );

    lua.new_usertype<FLAlertLayerProtocol>("FLAlertLayerProtocol",
        "FLAlert_Clicked", &FLAlertLayerProtocol::FLAlert_Clicked
    );

    lua.new_usertype<FLAlertLayer>("FLAlertLayer",
        "create", sol::overload(
            static_cast<FLAlertLayer* (*)(FLAlertLayerProtocol*, const char*, std::string, const char*, const char*, float, bool, float, float)>(&FLAlertLayer::create),
            static_cast<FLAlertLayer* (*)(FLAlertLayerProtocol*, const char*, std::string, const char*, const char*, float)>(&FLAlertLayer::create),
            static_cast<FLAlertLayer* (*)(FLAlertLayerProtocol*, const char*, std::string, const char*, const char*)>(&FLAlertLayer::create),
            static_cast<FLAlertLayer* (*)(const char*, const std::string&, const char*)>(&FLAlertLayer::create)
        ),
        "show", &FLAlertLayer::show
    );

    lua.new_usertype<GManager>("GManager",
        "setup", &GManager::setup,
        "loadDataFromFile", &GManager::loadDataFromFile,
        "save", &GManager::save
    );

    lua.new_usertype<GameManager>("GameManager",
        "get", &GameManager::get,
        "setPlayerBall", &GameManager::setPlayerBall,
        "setPlayerBird", &GameManager::setPlayerBird,
        "setPlayerColor", &GameManager::setPlayerColor,
        "setPlayerColor2", &GameManager::setPlayerColor2,
        "setPlayerColor3", &GameManager::setPlayerColor3,
        "setPlayerDart", &GameManager::setPlayerDart,
        "setPlayerDeathEffect", &GameManager::setPlayerDeathEffect,
        "setPlayerFrame", &GameManager::setPlayerFrame,
        "setPlayerGlow", &GameManager::setPlayerGlow,
        "setPlayerJetpack", &GameManager::setPlayerJetpack,
        "setPlayerRobot", &GameManager::setPlayerRobot,
        "setPlayerShip", &GameManager::setPlayerShip,
        "setPlayerShipStreak", &GameManager::setPlayerShipStreak,
        "setPlayerSpider", &GameManager::setPlayerSpider,
        "setPlayerStreak", &GameManager::setPlayerStreak,
        "setPlayerSwing", &GameManager::setPlayerSwing,
        "isColorUnlocked", &GameManager::isColorUnlocked,
        "isIconUnlocked", &GameManager::isIconUnlocked,
        "m_unkAnimationDict", &GameManager::m_unkAnimationDict,
        "m_unkAnimationDict2", &GameManager::m_unkAnimationDict2,
        "m_frameTimeForAnimation", &GameManager::m_frameTimeForAnimation,
        "m_framesForAnimation", &GameManager::m_framesForAnimation,
        "m_defaultFrames", &GameManager::m_defaultFrames,
        "m_switchModes", &GameManager::m_switchModes,
        "m_toFullscreen", &GameManager::m_toFullscreen,
        "m_reloading", &GameManager::m_reloading,
        "m_fix", &GameManager::m_fix,
        "m_unkBool1", &GameManager::m_unkBool1,
        "m_unkBool2", &GameManager::m_unkBool2,
        "m_vsyncEnabled", &GameManager::m_vsyncEnabled,
        "m_valueKeeper", &GameManager::m_valueKeeper,
        "m_unlockValueKeeper", &GameManager::m_unlockValueKeeper,
        "m_customObjectDict", &GameManager::m_customObjectDict,
        "m_adTimer", &GameManager::m_adTimer,
        "m_adCache", &GameManager::m_adCache,
        "m_unkBool3", &GameManager::m_unkBool3,
        "m_unkSize4_1", &GameManager::m_unkSize4_1,
        "m_unkDouble2", &GameManager::m_unkDouble2,
        "m_unkSize4_2", &GameManager::m_unkSize4_2,
        "m_unkSize4_3", &GameManager::m_unkSize4_3,
        "m_loaded", &GameManager::m_loaded,
        "m_googlePlaySignedIn", &GameManager::m_googlePlaySignedIn,
        "m_editorClipboard", &GameManager::m_editorClipboard,
        "m_unkSize4_4", &GameManager::m_unkSize4_4,
        "m_playLayer", &GameManager::m_playLayer,
        "m_levelEditorLayer", &GameManager::m_levelEditorLayer,
        "m_gameLayer", &GameManager::m_gameLayer,
        "m_unkPtr", &GameManager::m_unkPtr,
        "m_menuLayer", &GameManager::m_menuLayer,
        "m_inMenuLayer", &GameManager::m_inMenuLayer,
        "m_unknownVariable", &GameManager::m_unknownVariable,
        "m_unknownBool3", &GameManager::m_unknownBool3,
        "m_unknownPlayLayerBool", &GameManager::m_unknownPlayLayerBool,
        "m_unknownBool4", &GameManager::m_unknownBool4,
        "m_unknownBool5", &GameManager::m_unknownBool5,
        "m_playerUDID", &GameManager::m_playerUDID,
        "m_playerName", &GameManager::m_playerName,
        "m_commentsEnabled", &GameManager::m_commentsEnabled,
        "m_playerUserID", &GameManager::m_playerUserID
    );
}