/**
 * @file	CardManager.h
 * @brief	�J�[�h�S�̂̊Ǘ�
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "Card.h"


 /**
  * @class	CardManager
  * @brief  �J�[�h�S�̂��Ǘ�����N���X
  */
class CardManager : public HWComponent
{
	//
	// �����o�ϐ�
	//

public:

	//! �V���O���g���C���X�^���X
	static CardManager* instance;
	//! �J�[�h�̃C���X�^���X
	std::shared_ptr<Card> cards[CardTotalNumber];
	//! �f�b�L
	std::vector < std::shared_ptr<Card>> deck;
	//! �f�b�L(�ΐ푊��)
	std::vector < std::shared_ptr<Card>> deck_Opponent;
	//! �t�B�[���h(���[��1)
	std::vector < std::shared_ptr<Card>> field_1;
	//! �t�B�[���h(���[��2)
	std::vector < std::shared_ptr<Card>> field_2;
	//! ��D
	std::vector < std::shared_ptr<Card>> hand;
	//! ��D(�ΐ푊��)
	std::vector < std::shared_ptr<Card>> hand_Opponent;

	//! �I�𒆂̍���
	ItemList selectItem;
	//! �I�𒆂̃J�[�h
	std::shared_ptr<Card> selectCard;
	//! ���̃t���[�����ɕύX�������炳�ꂽ
	bool isUpdate = false;


	//
	// ���\�b�h
	//

public:

	/**
	 * @brief		�R���X�g���N�^
	 */
	CardManager();

	/**
	 * @brief		�f�X�g���N�^
	 */
	~CardManager();

	/**
	 * @brief		�����Ֆʂ��쐬
	 */
	void SetUp();

	/**
	 * @brief		�N���C�A���g�̏����Ֆʂ��쐬
	 */
	void SetUpCliant(Card*);

	/**
	 * @brief		�f�b�L���V���b�t������
	 */
	void Shuffle();

	/**
	 * @brief		�̈���W���X�V
	 * @param		�X�V����̈�
	 */
	void AreaNumberUpdate(Area);

	/**
	 * @brief		��D�̃J�[�h���L����
	 */
	void SpreadHand();

	/**
	 * @brief		�R�D����ꖇ����
	 * @return		? ����ɏI��(true) : �R�D���Ȃ����A��D�������ς�(false) 
	 */
	bool DrawFromDeck();
	
	/**
	 * @brief		�R�D����ꖇ����(�N���C�A���g)
	 * @return		? ����ɏI��(true) : �R�D���Ȃ����A��D�������ς�(false) 
	 */
	bool DrawFromDeckCliant();
	
	/**
	 * @brief		�I�����ڂ̈ړ�
	 * @param[in]	�ړ�����
	 */
	void MoveSelectItem(Direction);

	/**
	 * @brief		���ڃZ���N�g���̃A�N�V����
	 */
	void ItemSelect();

	/**
	 * @brief		�I�𒆂̃J�[�h������
	 */
	void SelectCardRelease();

	/**
	 * @brief		�I�𒆂̃J�[�h���t�B�[���h�ɏd�˂�
	 */
	void Overlap();

	/**
	 * @brief		�J�[�h�̗̈��ύX
	 * @param[in]	�ύX����J�[�h�̗̈���̍��W
	 * @param[in]	�ύX��̗̈�
	 */
	void CardAreaChange(int, Area);

	/**
	 * @brief		�J�[�h�̗̈��ύX
	 * @param[in]	�ύX����J�[�h�̃C���X�^���X
	 * @param[in]	�ύX��̗̈�
	 */
	void CardAreaChange(std::shared_ptr<Card>, Area);

	/**
	 * @brief		�̈�ƃJ�[�h���W����w��̃J�[�h��T��
	 * @param[in]	�J�[�h���W
	 * @param[in]	��������̈�
	 * @return		��������(���݂��Ȃ��ꍇ��nullptr)
	 */
	std::shared_ptr<Card> FindCard(int, Area);

	/**
	 * @brief		�R���X�g���N�^
	 */
	void GameJudge();

	/**
	 * @brief		�R���X�g���N�^
	 * @return		CardManager& �C���X�^���X
	 */
	static CardManager& Instance();

	/**
	 * @brief		�������֐�
	 */
	void Awake()override;

	/**
	 * @brief		�X�V����
	 */
	void Update()override;
};

