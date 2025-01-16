#pragma once
#include <stdarg.h>
#include <algorithm>
#include "HWComponent.h"
#include "HWTransform.h"
#include "HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		�R���|�[�l���g���Ǘ�����A���ׂẴI�u�W�F�N�g�����N���X�̒�`
*/


/**
 * @class	CopyType
 * @brief	�R�s�[�R���X�g���N�^�̃^�C�v
 */
enum class CopyType
{
	//! �V�����[�R�s�[(0)
	Shallow,
	//! �f�B�[�v�R�s�[(1)
	Deep,
};


/**
 * @class	HWGameObject
 * @brief	�I�u�W�F�N�g�Ɋւ�������܂Ƃ߂��N���X
 */
class HWGameObject
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HandlerWaltan;
	friend class CollisionWaltan;

private:

	/*     �����o�ϐ�     */

	/**
	 * @brief   �C���X�^���X�����ꂽ�I�u�W�F�N�g�S�Ă�ۊǂ��Ă����R���e�i
	 * @History 24/07/19 �쐬(Suzuki N)
	 */
	static std::vector<HWGameObject*> gameObjects;

	/**
	 * @brief		�A�^�b�`����Ă���S�ẴR���|�[�l���g
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	std::vector<std::unique_ptr<HWComponent>> hwComponents;

	/**
	 * @brief		�q�I�u�W�F�N�g
	 * @History		24/09/26 �쐬(Suzuki N)
	 */
	std::vector<HWGameObject*> children;

	/**
	 * @brief		�e�I�u�W�F�N�g
	 * @History		24/09/26 �쐬(Suzuki N)
	 */
	HWGameObject* parent;

public:

	/**
	 * @brief		�A�N�e�B�u
	 * @History		24/10/03 �쐬(Suzuki N)
	 */
	bool active;

	/**
	 * @brief		�I�u�W�F�N�g�̖��O
	 * @History		24/07/29 �쐬(Suzuki N)
	 */
	std::string name;

	/**
	 * @brief		�I�u�W�F�N�g�̃^�O(enum�Ȃǂŕʌ�`���Ă�������)
	 * @History		24/10/04 �쐬(Suzuki N)
	 */
	int tag;

	/**
	 * @brief		�n���h���[��Update���\�b�h�̗D�揇��(�~��)
	 * @History		24/07/21 �쐬(Suzuki N)
	 */
	int priority;

	/**
	 * @brief		Transform�R���|�[�l���g
	 * @History		24/09/26 �쐬(Suzuki N)
	 */
	HWTransform* transform;


private:

	/*     ���\�b�h     */

	/**
	 * @brief       �v���C�I���e�B���Q�Ƃ��ă\�[�g����(�~��)
	 * @author      Suzuki N
	 * @date        24/07/19
	 */
	void BubbleSort();

	/**
	 * @brief       �I�u�W�F�N�g���R�s�[����(�I�u�W�F�N�g�ƃ�������̃f�[�^�̃R�s�[)
	 * @param[in]	HWGameObject& �R�s�[���ɂȂ�I�u�W�F�N�g
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void DeepCopy(const HWGameObject& _other);

	/**
	 * @brief       �I�u�W�F�N�g���R�s�[����(�Q�Ƃ̃R�s�[)
	 * @param[in]	HWGameObject& �R�s�[���ɂȂ�I�u�W�F�N�g
	 * @author      Suzuki N
	 * @date        24/10/03
	 */
	void ShallowCopy(const HWGameObject& _other);

	/**
	 * @brief       �S�ẴR���|�[�l���g��Update���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllUpdates();

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionEnterCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionEnters(HWCollider& _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionStayCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionStays(HWCollider& _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionExitCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionExits(HWCollider& _collider);
	
	/**
	 * @brief       �S�ẴR���|�[�l���g��OnTriggerEnterCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerEnters(HWCollider& _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnTriggerStayCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerStays(HWCollider& _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnTriggerExitCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnTriggerExits(HWCollider& _collider);


public:

#pragma region �R���X�g���N�^

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject();

	/**
	 * @brief		�R���X�g���N�^(���O�̏������錾)
	 * @param[in]	std::string �I�u�W�F�N�g��
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const std::string& _name);

	/**
	 * @brief		�R���X�g���N�^(�v���C�I���e�B�̏������錾)
	 * @param[in]	int �v���C�I���e�B
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const int _priority);

	/**
	 * @brief		�R���X�g���N�^(���O�ƃv���C�I���e�B�̏������錾)
	 * @param[in]	std::string �I�u�W�F�N�g��
	 * @param[in]	int	�v���C�I���e�B
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const std::string& _name, const int _priority);

	/**
	 * @brief		�R�s�[�R���X�g���N�^
	 * @param[in]	HWGameObject& �R�s�[����HWGameObject
	 * @param[in]	const CopyType �R�s�[�̎��
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(const HWGameObject& _other, const CopyType copyType = CopyType::Deep);

#pragma endregion


	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	~HWGameObject();


#pragma region Getter���\�b�h�Q

	/**
	 * @brief		�R���|�[�l���g��ǉ�����
	 * @return		std::vector<HWGameObject*> World��̑S�Ă�GameObject���擾����
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	static std::vector<HWGameObject*> GetGameObjects(){ return gameObjects; }

	/**
	 * @brief		�S�Ă̎q�I�u�W�F�N�g���擾����
	 * @detail		�����œ���̃C���f�b�N�X�̎q�I�u�W�F�N�g���擾�ł���
	 * @return		const std::vector<HWGameObject*>& �S�Ă̎q�I�u�W�F�N�g���擾����
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	std::vector<HWGameObject*>& GetChildren() { return children; }

	/**
	 * @brief		�q�I�u�W�F�N�g���擾����
	 * @detail		�����œ���̃C���f�b�N�X�̎q�I�u�W�F�N�g���擾�ł���
	 * @return		const std::vector<HWGameObject*>& �S�Ă̎q�I�u�W�F�N�g���擾����
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	HWGameObject* GetChild(const int _index);

	/**
	 * @brief		�e�I�u�W�F�N�g���擾����
	 * @return		HWGameObject* �e�I�u�W�F�N�g 
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	HWGameObject* Parent() { return parent; }


#pragma endregion

#pragma region Setter���\�b�h�Q

	/**
	 * @brief		�e�I�u�W�F�N�g��ݒ肷��
	 * @param[in]	const int �擾����q�I�u�W�F�N�g�̃C���f�b�N�X
	 * @return		const std::vector<HWGameObject*>& �S�Ă̎q�I�u�W�F�N�g���擾����
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	void SetParent(HWGameObject* _parent);

#pragma endregion


	/**
	 * @brief		�R���|�[�l���g��ǉ�����
	 * @param[in]	std::unique_ptr<HWComponent> �A�^�b�`����R���|�[�l���g
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		//�e���v���[�g��Type��Component�̔h���N���X�����ׁA������ꍇ�̓R���p�C�����ɃG���[��f��
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Attempted to attach a non-component");


		std::unique_ptr<HWComponent> component = std::make_unique<T>(std::forward<Args>(args)...);

		// �R���|�[�l���g����A�^�b�`����Ă���GameObject��Transform���m�F�ł���悤�ɂ���
		component->gameObject = this;
		component->transform = (GetComponent<HWTransform>());
		hwComponents.push_back(std::move(component));

		T* ret = dynamic_cast<T*>(hwComponents.back().get());
		// �R���|�[�l���g���A�^�b�`���ꂽ�u�Ԃɑ��郁�\�b�h���Ăяo��
		ret->Awake();

		// �R���|�[�l���g���v���C�I���e�B���ɕ��ѕς���(�~��)
		std::sort(hwComponents.begin(), hwComponents.end(), 
			[](const std::unique_ptr<HWComponent>& a, const std::unique_ptr<HWComponent>& b) {
			return a->priority > b->priority; });

		return ret;
	}

	/**
	 * @brief		�w��̃R���|�[�l���g��Ԃ�
	 * @return		�A�^�b�`����Ă����ꍇ�̓C���X�^���X��Ԃ��A����ȊO�Ȃ�nullPtr��Ԃ�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T >
	T* GetComponent()
	{
		//�e���v���[�g��Type��Component�̔h���N���X�����ׁA������ꍇ�̓R���p�C�����ɃG���[��f��
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Trying to get something other than Component");

		//java��C#�ł����Ƃ����foreach�\��
		for (auto& component : hwComponents)
		{
			if (auto* targetComponent = dynamic_cast<T*>(component.get()))
				return targetComponent;
		}

		return nullptr;
	}
};