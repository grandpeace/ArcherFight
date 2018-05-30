#include "Bulletbase.h"

BulletBase::BulletBase()
{
	attpower = 5;
	flyspeed = 5;

}

BulletBase::~BulletBase()
{
}

bool BulletBase::init()
{
	return true;
}

BulletBase* BulletBase::create(Sprite *sprite)
{
	BulletBase* abullet = new BulletBase();
	return abullet;
}

void BulletBase::attacking(Player *player, BulletBase *Abullet,Point pos)
{
	float time = (Abullet->range) / (Abullet->flyspeed)*0.01;
	float length = sqrt((player->x_coord - pos.x)*(player->x_coord - pos.x) + (player->y_coord - pos.y)*(player->y_coord - pos.y));
	float xchange = (pos.x - player->x_coord) / length*Abullet->range;
	float ychange = (pos.y - player->y_coord) / length*Abullet->range;
	//��cocos2dx����������ѧ����

	auto moveBy = MoveBy::create(time, Point(xchange, ychange));



	Abullet->runAction(Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, Abullet)), NULL));
	//���ӵ�λ�ƶ������ӵ���ʧ�����ϲ������ڿ��Կ����ӵ�ͣ��Ч�������ڲ�д����Ϊ��ײ�ж����⡭��
	//��˵���������ִ�б߰��Լ��������ɾ���������Ȼ����bug������360ǿ��ж������ж��360��
}

bool BulletBase::collidePlayer(Player *player)
{
	return true;
}