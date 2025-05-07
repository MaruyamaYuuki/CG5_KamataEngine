#pragma once

#include <string>
#include <d3d12.h>

// Shaderクラス
class Shader {
public:
	// シェーダーファイルを読み込み、コンパイル済みデータを生成する
	void Load(const std::wstring& filePath, const std::string& shaderModel);

	// 生成したコンパイル済データを取得する
	ID3DBlob* GetBlob();

	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader();

private:
	ID3DBlob* blob_ = nullptr;
};
