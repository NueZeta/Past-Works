/**
 * @file	Player.h
 * @brief	プレイヤーの入力等の管理
 * @author	NS
 * @date	2024/1/2
 */

#pragma once
#include "Player.h"


Player::Player()
	: input(nullptr), udpConnection(nullptr)
{
}

Player::~Player()
{
}

void Player::SelectInputCallback(InputAction::CallBackContext _c)
{
	if (_c.state == InputState::Started)
		CardManager::Instance().ItemSelect();
}

void Player::MoveInputCallback(InputAction::CallBackContext _c)
{
	for (auto it = _c.key.begin(); it != _c.key.end(); ++it)
	{
		if (it->inputState != InputState::Started) continue;

		switch (it->keyCode)
		{
		case KEY_INPUT_A: 
			CardManager::Instance().MoveSelectItem(Direction::Left);
			break;

		case KEY_INPUT_D:
			CardManager::Instance().MoveSelectItem(Direction::Right);
			break;
		}
	}
}

void Player::ReceiveCallback(SendData& _data)
{
	CardManager::Instance().SetUpCliant(_data.cards);
}

void Player::Awake()
{
	//
	// 入力系の初期設定
	//

	input = std::make_unique<InputSystem>();

	input->AddKeyCode("move", {KEY_INPUT_A ,KEY_INPUT_D});
	input->AddCallBack("move", std::bind(&Player::MoveInputCallback, this, std::placeholders::_1));

	input->AddKeyCode("select", {KEY_INPUT_SPACE});
	input->AddCallBack("select", std::bind(&Player::SelectInputCallback, this, std::placeholders::_1));

	input->AddKeyCode("cancel", {KEY_INPUT_RETURN});
	input->AddCallBack("cancel", [&](InputAction::CallBackContext c) {
			if (c.state == InputState::Started) CardManager::Instance().SelectCardRelease(); });

	//
	// UDP通信の設定
	//

	udpConnection = std::make_unique<UdpConnection>(GameManager::ip, GameManager::port);
	udpConnection->SubscribeReceiveCallback(std::bind(&Player::ReceiveCallback, this, std::placeholders::_1));
}

void Player::Update()
{
	if (GameManager::param != GameParameter::Game) return;

	if (CheckHitKey(KEY_INPUT_Z) && CheckHitKey(KEY_INPUT_X) && CheckHitKey(KEY_INPUT_C))
	{
		CardManager::Instance().hand.clear();
		CardManager::Instance().deck.clear();
		CardManager::Instance().isUpdate = true;
	}


	if (CardManager::Instance().isUpdate)
	{
		auto CM = CardManager::Instance();

		SendData data;
		data.sendTime = 123;

		udpConnection->Send(data);
		CardManager::Instance().isUpdate = false;
	}

	// データ受信を監視
	udpConnection->RxSurveillance();

	if (GameManager::isLose || GameManager::isWin)
		GameManager::param = GameParameter::Result;
}
