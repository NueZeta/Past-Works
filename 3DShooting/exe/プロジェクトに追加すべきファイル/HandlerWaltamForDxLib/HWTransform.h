#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"

class HWGameObject;

/**
* @author   Suzuki N
* @date     24/07/16
* @note		���W�n�̏���ێ�����R���|�[�l���g�̒�`
*/


/**
 * @class	HWTransform
 * @brief	�I�u�W�F�N�g�̍��W���]�Ȃǂ�ێ�����R���|�[�l���g
 */
class HWTransform : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

#pragma region �O���[�o��

	/**
	 * @brief		�O���[�o�����W
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR position;

	/**
	 * @brief		�O���[�o����]
	 * @History		24/06/17 �쐬(Suzuki N)
	 */

	VECTOR rotate;

	/**
	 * @brief		�O���[�o���g�k
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR scale;

	/**
	 * @brief		�O���[�o���ϊ��s��
	 * @History		24/09/15 �쐬(Suzuki N)
	 */
	MATRIX globalMat;

#pragma endregion

#pragma region ���[�J��

	/**
	 * @brief		���[�J�����W
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR localPosition;

	/**
	 * @brief		���[�J����]
	 * @History		24/06/17 �쐬(Suzuki N)
	 */

	VECTOR localRotate;

	/**
	 * @brief		���[�J���g�k
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR localScale;

#pragma endregion

	/**
	 * @brief		�ړ��x�N�g��
	 * @History		24/09/26 �쐬(Suzuki N)
	 */
	VECTOR velocity;

	/**
	 * @brief		���ʕ����̃x�N�g��
	 * @History		24/09/26 �쐬(Suzuki N)
	 */
	VECTOR forward;


	/*     ���\�b�h     */


private:

	/**
	 * @brief		���s�ړ��A��]�A�g�k��ݒ肷��
	 * @author		Suzuki N
	 * @date		24/09/15
	 */
	void SetMatrix();

public:

	/**
	 * @brief		�^�[�Q�b�g�̂ق��֌���
	 * @param[in]	const VECTOR&	�^�[�Q�b�g�̍��W
	 * @author		Suzuki N
	 * @date		24/10/09
	 */
	void LookAt(const VECTOR& _target);

#pragma region �R���X�g���N�^

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	HWTransform();

	/**
	 * @brief		�f�X�g���N�^
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/09/17
	 */
	~HWTransform(){}

#pragma endregion

protected:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Update() override;

#pragma endregion
};