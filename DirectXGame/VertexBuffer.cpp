#include "VertexBuffer.h"
#include "KamataEngine.h"

#include <d3dx12.h>
#include <cassert>

using namespace KamataEngine;

void VertexBuffer::Create(const UINT size, const UINT stride) {
	// クラス内で取得するために追加
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 頂点リソースの生成
	// 頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	// 頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = size;
	// バッファの場合はこれらは1にする決まり
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	// バッファの場合はこれにする決まり
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際に頂点リソースを生成する
	ID3D12Resource* vertexResource = nullptr;
	HRESULT hr =dxCommon->GetDevice()->CreateCommittedResource(
		&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexResourceDesc, 
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(hr));

	// 生成した頂点リソース をとっておく
	vertexBuffer_ = vertexResource;

		// VertexBufferViewを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// リソースの先頭アドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView.SizeInBytes = size;
	// 1つの頂点サイズ
	vertexBufferView.StrideInBytes = stride;

	// VertexBufferView をとっておく
	vertexBufferView_ = vertexBufferView;
}

ID3D12Resource* VertexBuffer::Get() { 
	return vertexBuffer_; 
}

D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::GetView() { 
	return &vertexBufferView_; }

VertexBuffer::VertexBuffer() {}

VertexBuffer::~VertexBuffer() {
	if (vertexBuffer_) {
		vertexBuffer_->Release();
		vertexBuffer_ = nullptr;

	}
}
