#include "TollgateScene.h"
#include "Player.h"
#include "BulletBase.h"
#include <math.h>
#define k_w (EventKeyboard::KeyCode)119
#define k_a (EventKeyboard::KeyCode)97
#define k_s (EventKeyboard::KeyCode)115
#define k_d (EventKeyboard::KeyCode)100

Scene* TollgateScene::createScene() 
{
    auto scene = Scene::create();
    auto layer = TollgateScene::create();

    scene->addChild(layer);

	return scene;
}

bool TollgateScene::init() 
{
    if (!Layer::init())
        return false;

	Size visibleSize = CCDirector::getInstance()->getVisibleSize();

	m_player = Player::create();
	m_player->bindSprite(Sprite::create("player1.png"));
	m_player->setPosition(Point(m_player->x_coord, m_player->y_coord));
    this->addChild(m_player);

	n_player = Player::create();
	n_player->bindSprite(Sprite::create("player2.png"));
	n_player->setPosition(Point(n_player->x_coord, n_player->y_coord));
	this->addChild(n_player);

	this->scheduleUpdate();

    return true;
}
//��Ҳ��֪��onEnter��ʲô��˼ֻ�����ų��ģ�ֻ֪�������Ǽ����
void TollgateScene::onEnter()
{
	Layer::onEnter();

	auto keylistener = EventListenerKeyboard::create();
	//���̼����������������ƶ�
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys[keyCode] = true;
	};

	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys[keyCode] = false;
	};

	EventDispatcher *eventDispatcher1 = Director::getInstance()->getEventDispatcher();
	eventDispatcher1->addEventListenerWithSceneGraphPriority(keylistener, this);


	auto touchlistener = EventListenerTouchOneByOne::create();
	//�������������������﹥��
	touchlistener->onTouchBegan = [&](Touch* touch, Event *event)
	{
		touchon = true;
		Point pos1 = touch->getLocationInView();
		Point pos2 = Director::getInstance()->convertToGL(pos1);
		pos = pos2;//�õ���������
		return true;
	};
	touchlistener->onTouchEnded = [&](Touch* toych, Event *event)
	{
		touchon = false;
	};

	EventDispatcher *eventDispatcher2 = Director::getInstance()->getEventDispatcher();
	eventDispatcher2->addEventListenerWithSceneGraphPriority(touchlistener, this);

}

void TollgateScene::update(float delta)
{
	if (keys[k_w] || keys[k_a] || keys[k_s] || keys[k_d])//�ֱ���wasd���μ�#define
	{
		runEvent();
	}

	if (!touchon)
	{
		once = true;
	}
	if (touchon&&once)
	{
		attack();
		once = false;
	}
	//������¼���ͨ��ǰ���⼸�в�������ʹ����һ��ʱ������һ�Σ�ԭ������Ƹ�����CD����δ֪ԭ��BUG���޹�
}
//�����ܶ��ĺ��������������Ϊ������һ�鲻����д�ġ�����ʱ���Ÿİ�
void TollgateScene::runEvent()
{
	m_player->run(m_player, keys);

}

void TollgateScene::attack()
{


    log("attack in x = %f  y = %f", pos.x, pos.y);
	auto Abullet = BulletBase::create();
	Abullet->bindSprite(Sprite::create("bullet.png"));
	Abullet->setPosition(Point(m_player->x_coord, m_player->y_coord));
	this->addChild(Abullet);

	Abullet->attacking(m_player, Abullet, pos);
}