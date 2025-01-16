#pragma once
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/09/11
* @note		InputSystem�֌W���܂Ƃ߂��w�b�_�[�t�@�C��
*/

/**
* @enum		InputState
* @brief	InputSystem�̓��̓p�����[�^
*/
enum class InputState
{
	//! ���͑҂�(0)
	Waiting,
	//! ���͂����u��(1)
	Started,
	//! ���͒�(2)
	Performed,
	//! ���͏I��(3)
	Canceled,
};

/**
* @struct	KeyInfo
* @brief	�L�[���
*/
struct KeyInfo
{
	//! �L�[�R�[�h
	int keyCode;
	//! ���͎���
	unsigned int inputTyme;
	//! �{�^�����͂̃p�����[�^
	InputState inputState;
};

/**
 * @class	InputAction
 * @brief	�A�N�V�����}�b�v�̏��
 */
class InputAction
{
	friend class InputSystem;

public:
	/**
	* @struct	CallBackContext
	* @brief	�R�[���o�b�N�œn�����
	*/
	struct CallBackContext
	{
		//! InputAction�̃p�����[�^
		const InputState state;
		//! ���͂����Ƃ��̎���(ms)
		const unsigned int inputTyme;
		//! �o�^����Ă���L�[
		const std::vector<KeyInfo> key;
	};

private:
	/*     �����o�ϐ�     */

	/**
	 * @brief		�L�[���
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	std::vector<KeyInfo> keyInfoVec;

	/**
	 * @brief		�o�^���ꂽ�R�[���o�b�N�֐�
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	std::unordered_map<int, std::function<void(const CallBackContext&)>> callBacks;

	/**
	 * @brief		InputAction�̃p�����[�^�[
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	InputState inputState;

	/**
	 * @brief		�o�^�����R�[���o�b�N�֐���ID
	 * @History		24/10/02 �쐬(Suzuki N)
	 */
	int nextId;


private:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction() : inputState(InputState::Waiting), nextId(0)
	{
	}

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const int _keyCode) : inputState(InputState::Waiting), nextId(0)
	{
		AddKeyCode(_keyCode);
	}

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputAction(const std::vector<int> _keyCodeVec) : inputState(InputState::Waiting), nextId(0)
	{
		AddKeyCode(_keyCodeVec);
	}

public:

	/**
	 * @brief		�A�N�V�����}�b�v�̃X�e�[�^�X��Ԃ�
	 * return		InputStatus	�A�N�V�����}�b�v�̃X�e�[�^�X
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputState GetInputState() { return inputState; }

	/**
	 * @brief		�L�[����Ԃ�
	 * return		std::vector<KeyInfo>	�o�^���ꂽ�L�[���
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo> GetKeyInfoVec() { return keyInfoVec; }

private:

	/**
	 * @brief		�L�[����Ԃ�
	 * return		std::vector<KeyInfo>	�o�^���ꂽ�L�[���
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo>& GetKeyInfoRef() { return keyInfoVec; }

	/**
	 * @brief		�A�N�V�����}�b�v�̃X�e�[�^�X��ύX����
	 * param[in]	InputStatus	�A�N�V�����}�b�v�̃X�e�[�^�X
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void SetInputState(const InputState _state) { inputState = _state; }

	/**
	 * @brief		�o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void CallCallbacks(const InputAction::CallBackContext& _context)
	{
		for (auto it = callBacks.begin(); it != callBacks.end(); ++it)
			if(it->second)
				(it->second)(_context);
	}

	/**
	 * @brief		�L�[�R�[�h��ǉ�����
	 * @detail		{} �ŕ����I���\
	 * @param[in]	int �ǉ�����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const int _keyCode)
	{
		//! �o�^����L�[���̏������錾
		KeyInfo keyInfo =
		{
			_keyCode,
			0,
			InputState::Waiting,
		};

		// �L�[����o�^
		keyInfoVec.push_back(keyInfo);
	}

	/**
	 * @brief		�L�[�R�[�h��ǉ�����
	 * @detail		{} �ŕ����I���\
	 * @param[in]	std::vector<int> �ǉ�����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const std::vector<int> _keyCodeVec)
	{
		for (auto it = _keyCodeVec.begin(); it != _keyCodeVec.end(); ++it)
		{
			//! �o�^����L�[���̏������錾
			KeyInfo keyInfo =
			{
				*it,
				0,
				InputState::Waiting,
			};

			// �L�[����o�^
			keyInfoVec.push_back(keyInfo);
		}
	}

	/**
	 * @brief		�R�[���o�b�N�֐���ǉ�����
	 * @param[in]	std::function<void(InputAction::CallBackContext&>)> �ǉ�����R�[���o�b�N�֐�
	 * @return		const int	�o�^�����R�[���o�b�N�֐���ID
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	int AddCallBack(const std::function<void(const InputAction::CallBackContext&)> _callBack)
	{
		callBacks[nextId] = _callBack;
		return nextId++;
	}

	/**
	 * @brief		�R�[���o�b�N�֐����폜����
	 * @param[in]	std::string	�폜����L�[�̑��݂���L�[�}�b�v
	 * @param[in]	const int	�폜����R�[���o�b�N�֐���ID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void DeleteCallBack(const int _id)
	{
		// �L�[�R�[�h�����݂��Ă���΍폜����
		for (auto& it : callBacks)
			if(it.first == _id)
				it.second = nullptr;
	}
};

// �O���錾
class HandlerWaltan;

/**
 * @class	InputSystem
 * @brief	���͂̌��m�A���͎��ɃR�[���o�b�N�֐����ĂԃN���X
 */
class InputSystem
{
private:

	friend class HandlerWaltan;

	/*     �����o�ϐ�     */

	/**
	 * @brief		�A�N�e�B�u
	 * @History		24/09/07 �쐬(Suzuki N)
	 */
	bool active;

	/**
	 * @brief		�L�[�}�b�v
	 * @History		24/09/07 �쐬(Suzuki N)
	 */
	std::unordered_map<std::string, InputAction*> keyMap;

	/**
	 * @brief		�������ꂽInputSystem�̃C���X�^���X
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	static std::vector<InputSystem*> inputSystemVec;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	InputSystem() : active(true)
	{
		inputSystemVec.push_back(this);
	}

	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	~InputSystem()
	{
		// keyMap���폜
		for (auto ptr : keyMap)
			delete ptr.second;
		keyMap.clear();

		// �o�^���Ă���InputSystem�̓o�^��������
		auto it = std::find(inputSystemVec.begin(), inputSystemVec.end(), this);
		if (it != inputSystemVec.end())
			inputSystemVec.erase(it);
	}

	/**
	 * @brief		Active��ύX����
	 * @param[in]	bool �ύX���bool�l
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void SetActive(const bool _active) { active = _active; }


#pragma region �L�[�R�[�h�ǉ�

	/**
	 * @brief		�}�b�v�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	std::string&	�o�^����L�[
	 * @param[in]	const int		�L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string& _key, const int _inputKey)
	{
		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
		{
			if (it->second->keyInfoVec.size() > 0)
				// �L�[�R�[�h�����łɓo�^�ς݂łȂ����
				for (auto it2 = it->second->keyInfoVec.begin(); it2 != it->second->keyInfoVec.end(); ++it2)
					if (it2->keyCode == _inputKey)
						return;

			it->second->AddKeyCode(_inputKey);
		}
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃA�N�V�����}�b�v���쐬����
		else
			keyMap[_key] = new InputAction(_inputKey);
	}

	/**
	 * @brief		�}�b�v�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	const std::string&		 �o�^����L�[
	 * @param[in]	const std::vector<int>&  �L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string& _key, const std::vector<int>& _inputKey)
	{
		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
		{
			if (it->second->keyInfoVec.size() > 0)
				// �L�[�R�[�h�����łɓo�^�ς݂łȂ����
				for (auto it2 = it->second->keyInfoVec.begin(); it2 != it->second->keyInfoVec.end(); ++it2)
					for (auto keyIt = _inputKey.begin(); keyIt != _inputKey.end(); ++keyIt)
						if (it2->keyCode == *keyIt)
							break;

			it->second->AddKeyCode(_inputKey);
		}
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃA�N�V�����}�b�v���쐬����
		else
			keyMap[_key] = new InputAction(_inputKey);
	}

#pragma endregion

#pragma region �L�[�R�[�h�폜

	/**
	 * @brief		�}�b�v�ɓo�^�����L�[�R�[�h���폜����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	const std::string&	�폜����L�[�̑��݂���L�[�}�b�v
	 * @param[in]	const int			�폜����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void DeleteKeyCode(const std::string& _key, const int _inputKey)
	{
		// �L�[�}�b�v�����݂��Ȃ��ꍇ�͂��̂܂܏I��
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// �L�[�R�[�h�����݂��Ă���΍폜����
		for (auto it = keyMapIt->second->keyInfoVec.begin(); it != keyMapIt->second->keyInfoVec.end(); ++it)
			if (it->keyCode == _inputKey)
			{
				keyMapIt->second->keyInfoVec.erase(it);
				break;
			}
	}

	/**
	 * @brief		�}�b�v�ɓo�^�����L�[�R�[�h���폜����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	const std::string&			�폜����L�[�̑��݂���L�[�}�b�v
	 * @param[in]	const std::vector<int>&		�폜����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void DeleteKeyCode(const std::string& _key, const std::vector<int> _inputKey)
	{
		// �L�[�}�b�v�����݂��Ȃ��ꍇ�͂��̂܂܏I��
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		for(auto keyCodeIt = _inputKey.begin(); keyCodeIt != _inputKey.end(); ++keyCodeIt)
		{
			// �L�[�R�[�h�����݂��Ă���΍폜����
			for (auto it = keyMapIt->second->keyInfoVec.begin(); it != keyMapIt->second->keyInfoVec.end(); ++it)
				if (it->keyCode == *keyCodeIt)
				{
					keyMapIt->second->keyInfoVec.erase(it);
					break;
				}
		}
	}

#pragma endregion

#pragma region �R�[���o�b�N�ǉ�

	/**
	 * @brief		InputAction�ɃR�[���o�b�N�֐���o�^����
	 * @param[in]	std::string&	�o�^����L�[
	 * @param[in]	std::function<void(InputAction::CallBackContext&)> �o�^����R�[���o�b�N�֐�
	 * @return		int	�o�^�����R�[���o�b�N�֐���ID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	int AddCallBack(const std::string& _key, const std::function<void(const InputAction::CallBackContext&)> _callBack)
	{
		//! �o�^�����R�[���o�b�N�֐���ID
		int id = -1;

		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
			id = it->second->AddCallBack(_callBack);
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃA�N�V�����}�b�v���쐬����
		else
		{
			keyMap[_key] = new InputAction();
			id = keyMap[_key]->AddCallBack(_callBack);
		}

		// �o�^����ID��Ԃ�
		return id;
	}

#pragma endregion

#pragma region �R�[���o�b�N�폜

	/**
	 * @brief		InputAction�ɃR�[���o�b�N�֐���o�^����
	 * @param[in]	std::string	�폜����L�[�̑��݂���L�[�}�b�v
	 * @param[in]	const int	�폜����R�[���o�b�N�֐���ID
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void DeleteCallBack(const std::string& _key, const int _id)
	{
		// �L�[�}�b�v�����݂��Ȃ��ꍇ�͂��̂܂܏I��
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// �L�[�R�[�h�����݂��Ă���΍폜����
		keyMapIt->second->DeleteCallBack(_id);
	}

#pragma endregion

#pragma region �L�[�}�b�v�폜

	/**
	 * @brief		�o�^����Ă���L�[�}�b�v���폜����
	 * @param[in]	std::string& _key �폜����L�[�}�b�v�̃L�[
	 * @author		Suzuki N
	 * @date		24/10/02
	 */
	void DeleteKeyMap(const std::string& _key)
	{
		// �L�[�}�b�v�����݂��Ȃ��ꍇ�͂��̂܂܏I��
		auto keyMapIt = keyMap.find(_key);
		if (keyMapIt == keyMap.end())
			return;

		// �폜����
		keyMap.erase(keyMapIt);
	}

#pragma endregion



private:

	/**
	 * @brief		�A�N�V�����}�b�v�ɓo�^����Ă���L�[���Ď�����
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheck()
	{
		// �o�^����Ă���L�[�̓��͏�Ԃ��Ď�
		for (auto it = keyMap.begin(); it != keyMap.end(); ++it)
		{
			//! ���̃A�N�V�����}�b�v���œ��͂���������
			bool isInput = false;
			//! ���͎���
			unsigned int inputTyme = 0;

			for (auto it2 = it->second->GetKeyInfoRef().begin(); it2 != it->second->GetKeyInfoRef().end(); ++it2)
			{
				// �o�^���ꂽ�L�[�̓��͏�Ԃ��m�F
				if (CheckHitKey((*it2).keyCode))
				{
					// ���͂�������
					isInput = true;

					// �L�[�̓��͏�ԂŃp�����[�^�[��ς���
					switch ((*it2).inputState)
					{
					case InputState::Waiting:
						(*it2).inputState = InputState::Started;
						// ���s���Ԃ�ۊ�
						inputTyme = (*it2).inputTyme = GetNowCount();
						break;

					case InputState::Started:
						// ���͒��Ƀp�����[�^�[��ύX
						(*it2).inputState = InputState::Performed;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Performed:
						// ������Ԃ̌p���Ȃ��߁A�p�����[�^�[�̕ύX�͂Ȃ�
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Canceled:
						(*it2).inputState = InputState::Started;
						// ���s���Ԃ�ۊ�
						inputTyme = (*it2).inputTyme = GetNowCount();
						break;
					}
				}
				// ���͂��Ȃ�����
				else
				{
					// �L�[�̓��͏�ԂŃp�����[�^�[��ς���
					switch ((*it2).inputState)
					{
					case InputState::Waiting:
						inputTyme = (*it2).inputTyme;
						// �ҋ@��Ԃ��p�����Ă��邽�߁A�ύX�Ȃ�
						break;

					case InputState::Started:
						// ���͏I���̃p�����[�^�[�ɕύX
						(*it2).inputState = InputState::Canceled;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Performed:
						// ���͏I���̃p�����[�^�[�ɕύX
						(*it2).inputState = InputState::Canceled;
						inputTyme = (*it2).inputTyme;
						break;

					case InputState::Canceled:
						// ���͑ҋ@�̃p�����[�^�[�ɕύX
						(*it2).inputState = InputState::Waiting;
						inputTyme = (*it2).inputTyme;
						break;
					}
				}
			}

			// ���͂��������ꍇ
			if (isInput)
			{
				// �L�[�}�b�v��InputStatus��ύX����
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					it->second->SetInputState(InputState::Started);
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Performed);
					break;
				case InputState::Performed:
					// ���͏�Ԃ��p���Ȃ��߁A�X�e�[�^�X�̕ύX�Ȃ�
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Started);
					break;
				}
				// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
				it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, it->second->GetKeyInfoVec(),});
			}
			// ���͂��Ȃ������ꍇ
			else
			{
				// �L�[�}�b�v��InputStatus��ύX����
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					// ���͏�Ԃ��p���Ȃ��߁A�X�e�[�^�X�̕ύX�Ȃ�
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Canceled);
					// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
					it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, it->second->GetKeyInfoVec(), });
					break;
				case InputState::Performed:
					it->second->SetInputState(InputState::Canceled);
					// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
					it->second->CallCallbacks({ it->second->GetInputState(),inputTyme, it->second->GetKeyInfoVec(), });
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Waiting);
					break;
				}
			}
		}
	}

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void Update()
	{
		KeyCheck();
	}
};