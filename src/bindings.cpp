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