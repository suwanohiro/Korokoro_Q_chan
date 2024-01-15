#include "EffectManager.hpp"

EffectManager::EffectManager()
{
}

bool EffectManager::Load()
{
	const CSVData texturePaths = FileAction::ReadCSV("Recource/Image/Effect/EffectList.swn");

	for (int cnt = 0; cnt < texturePaths.size(); cnt++) {
		const std::string path = texturePaths[cnt][0];

		spCTexture work(new CTexture());
		const bool result = work->Load(path.c_str());

		// 読み込みに失敗したらここで処理終了
		if (!result) return false;

		_effectTexture.push_back(work);
	}

	return true;
}

void EffectManager::FixedUpdate()
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];
		work->FixedUpdate();
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

		// エフェクト要素が無効状態ならば要素を削除する
		if (!work->isActive()) _effectArray.erase(_effectArray.begin() + cnt);
	}
}

void EffectManager::Render(Vector2 value)
{
	for (int cnt = 0; cnt < _effectArray.size(); cnt++) {
		const spEffect work = _effectArray[cnt];

		work->Render(value);
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
	spEffect work(new Effect());
	work->setTexture(texture);
	work->Initialize(pos);
	work->Start(pos);

	_effectArray.push_back(work);
}
