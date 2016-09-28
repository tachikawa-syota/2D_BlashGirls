/**
* @file   CharacterFactory.h
* @brief  �L�����N�^�[�̃C���X�^���X�𐶐�����
* @author Syota Tachikawa
*/

#ifndef ___CHARACTERFACTORY_H
#define ___CHARACTERFACTORY_H

#include "..\IPlayer.h"
#include "Lilia.h"
#include "Runa.h"

/**
* @brief �L�����N�^�[�����N���X
*/
class CharacterFactory
{
public:
	/**
	* @brief �L�����N�^�[�C���X�^���X����
	* @param name - �L�����N�^�[�̖��O(Enum�Œ�`���Ă��镨���g�p)
	* @param index - �v���C���[�̔ԍ�
	*/
	IPlPtr CreateCharacter(const int name, const int index);
};

/**
* @brief �L�����N�^�[�C���X�^���X����
* @param name - �L�����N�^�[�̖��O(Enum�Œ�`���Ă��镨���g�p)
* @param index - �v���C���[�̔ԍ�
*/
IPlPtr CharacterFactory::CreateCharacter(const int name, const int index)
{
	switch (name)
	{
		// �����A
	case CharaName::LILIA:
		return make_shared<Lilia>(index);
		break;
		// ���i
	case CharaName::RUNA:
		return make_shared<Runa>(index);
		break;
		// �G���[�i���蓾�Ȃ��j
	default:
		return nullptr;
		break;
	}
}

#endif
