#include "EffectManager.hpp"

spCTexture EffectManager::__getTexture(EffectType type)
{
	if ((int)type < _effectTexture.size()) return _effectTexture[(int)type];
	return nullptr;
}

EffectManager::EffectManager()
	: _effectTexture()
	, _effectArray()
{
}

bool EffectManager::Load()
{
	const CSVData texturePaths = FileAction::ReadCSV("Recource/Image/Effect/EffectList.swn");

	for (int cnt = 0; cnt < texturePaths.size(); cnt++) {
		const std::string path = texturePaths[cnt][0];

		if (path == "") continue;

		spCTexture work(new CTexture());
		const bool result = work->Load(path.c_str());

		// �ǂݍ��݂Ɏ��s�����炱���ŏ����I��
		if (!result) return false;

		_effectTexture.push_back(work);
	}

	return true;
}

void EffectManager::FixedUpdate(Vector2 scroll)
{
	const int a = _effectArray.size();
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->FixedUpdate(scroll);
	}
}

void EffectManager::Update()
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->Update();
	}
}

void EffectManager::LateUpdate()
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->LateUpdate();

		// �G�t�F�N�g�v�f��������ԂȂ�Ηv�f���폜����
		if (!work->isActive()) _effectArray.erase(_effectArray.begin() + cnt);
	}
}

void EffectManager::Render()
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->Render();
	}
}

void EffectManager::Release()
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->Release();
	}

	for (int cnt = 0; cnt < _effectTexture.size(); cnt++) {
		const spCTexture work = _effectTexture[cnt];
		work->Release();
	}
}

void EffectManager::startEffect(EffectType type, Vector2 pos)
{
	spCTexture texture = __getTexture(type);

	if (texture == nullptr) {
		OutputDebugString("[ Error ] �G�t�F�N�g�e�N�X�`�����擾�ł��܂���ł����B\n");
		return;
	}

	spEffect work(new Effect());
	work->setTexture(texture);
	work->Initialize(pos);
	work->Start(pos);

	_effectArray.push_back(work);
}
