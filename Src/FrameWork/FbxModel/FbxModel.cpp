#include "pch.h"
#include "FbxModel.h"

//�R���X�g���N�^
FbxModel::FbxModel()
	:m_pRasterizerState(nullptr),
	m_pVertexShader(nullptr),
	m_pVertexLayout(nullptr),
	m_pPixelShader(nullptr),
	m_pConstantBuffer(nullptr),
	m_pVerBuffer(nullptr),
	m_pIndBuffer(nullptr),
	m_AnimStackNumber(0),
	m_frameTime(),
	m_timeCount(),
	m_start(),
	m_stop(),
	m_pFbxManager(nullptr),
	m_pFbxImporter(nullptr),
	m_pFbxScene(nullptr),
	m_fbxMeshNameArray{},
	m_pfbxMeshArray{},
	m_pDevice(nullptr),
	m_pContext(nullptr),
	m_pRenderTargetView(nullptr),
	m_vp{},
	m_isAnimation(false)
{


}

//�f�X�g���N�^
FbxModel::~FbxModel()
{
	if (m_pRasterizerState != nullptr)
	{
		//delete m_pRasterizerState;
		m_pRasterizerState->Release();
		m_pRasterizerState = nullptr;
	}
	if (m_pVertexShader != nullptr)
	{
		//delete m_pVertexShader;
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
	if (m_pVertexLayout != nullptr)
	{
		//delete m_pVertexLayout;
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}
	if (m_pPixelShader != nullptr)
	{
		//delete m_pPixelShader;
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}
	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
		//delete m_pConstantBuffer;
		m_pConstantBuffer = nullptr;
	}
	if (m_pVerBuffer != nullptr)
	{
		//delete m_pVerBuffer;
		m_pVerBuffer->Release();
		m_pVerBuffer = nullptr;
	}
	if (m_pIndBuffer != nullptr)
	{
		//
		m_pIndBuffer->Release();
		//delete m_pIndBuffer;
		m_pIndBuffer = nullptr;
	}
	if (m_pFbxManager != nullptr)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = nullptr;
	}
	//m_pFbxImporter->Destroy();
	if (m_pFbxImporter != nullptr)
	{
		m_pFbxImporter = nullptr;
	}
	if (m_pFbxScene != nullptr)
	{
		//m_pFbxScene->Destroy();
		m_pFbxScene = nullptr;
	}
	m_pfbxMeshArray.clear();

	if (m_pDevice != nullptr)
	{
		//m_pDevice->Release();
		m_pDevice = nullptr;
	}
	if (m_pContext != nullptr)
	{
		m_pContext = nullptr;
	}
	if (m_pRenderTargetView != nullptr)
	{
		
		m_pRenderTargetView = nullptr;
	}




}

///////////////////////////
//�t�@�C���̓ǂݍ���
//����:�E�B���h�E,�f�o�C�X�A�R���e�L�X�g�A��񂾁[���[�����Ƃт�[�A�t�@�C�����A�A�j���[�V�����p�t���O�A
//�߂�l:
//////////////////////////
bool FbxModel::Load(HWND window, ID3D11Device * pDevice, ID3D11DeviceContext * pContext, ID3D11RenderTargetView * pRenderTargetView, const char * fileName, bool isAnimation, int animStackNumber)
{
	//null�`�F�b�N
	if (!pDevice)return false;
	if (!pContext)return false;
	if (!pRenderTargetView)return false;
	if (!fileName)return false;

	m_pDevice = pDevice;
	m_pContext = pContext;
	m_pRenderTargetView = pRenderTargetView;
	//m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), NULL);

	//�p�C�v���C������
	RECT csize;
	GetClientRect(window, &csize);
	int cWidth = csize.right;
	int cHeight = csize.bottom;

	m_window = window;

	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 1;
	scd.BufferDesc.Width = cWidth;
	scd.BufferDesc.Height = cHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = window;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;
	D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &fl, 1, D3D11_SDK_VERSION, &scd, &m_pSwapChain, &m_pDevice, NULL, &m_pContext);
	
	ID3D11Texture2D *pTex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pTex);
	m_pDevice->CreateRenderTargetView(pTex, NULL, &m_pRenderTargetView);
	pTex->Release();

	m_pDevice = pDevice;
	m_pContext = pContext;
	m_pRenderTargetView = pRenderTargetView;

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)cWidth;
	vp.Height = (FLOAT)cHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	m_vp = vp;

	//�V�F�[�_�[�̐ݒ�
	ID3DBlob* pCompileVS = nullptr;
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Resources/Shaders/shader.hlsl",
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		NULL,
		0,
		&pCompileVS,
		NULL);
	assert(pCompileVS && "pCompileVS is nullptr");
	pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &m_pVertexShader);

	D3DCompileFromFile(L"Resources/Shaders/shader.hlsl",
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		NULL,
		0,
		&pCompilePS,
		NULL);
	assert(pCompilePS && "pCompilePS is nullptr");
	pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &m_pPixelShader);

	//���_���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE",0, DXGI_FORMAT_R32G32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};
	pDevice->CreateInputLayout(
		layout, 
		ARRAYSIZE(layout), 
		pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(), 
		&m_pVertexLayout);

	pCompileVS->Release();
	pCompilePS->Release();

	//�萔�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(ConstantBuffer);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	(pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer));


	//FBX Manager�쐬
	m_pFbxManager = FbxManager::Create();
	if (!m_pFbxManager)return false;

	//FBX Importer�쐬
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	if (!m_pFbxImporter)return false;

	//�������A�t�@�C���ǂݍ���
	m_pFbxImporter->Initialize(fileName);
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "model");
	m_pFbxImporter->Import(m_pFbxScene);

	FbxGeometryConverter converter(m_pFbxManager);

	converter.SplitMeshesPerMaterial(m_pFbxScene, true);
	converter.Triangulate(m_pFbxScene, true);

	if (isAnimation)
	{
		m_isAnimation = true;
		FbxArray<FbxString*> animStackNameArray;
		m_pFbxScene->FillAnimStackNameArray(animStackNameArray);
		m_AnimStackNumber = animStackNumber;
		FbxAnimStack* animationStack = m_pFbxScene->FindMember < FbxAnimStack>(animStackNameArray[m_AnimStackNumber]->Buffer());
		m_pFbxScene->SetCurrentAnimationStack(animationStack);
		FbxTakeInfo* takeInfo = m_pFbxScene->GetTakeInfo(*(animStackNameArray[animStackNumber]));
		m_start = takeInfo->mLocalTimeSpan.GetStart();
		m_stop = takeInfo->mLocalTimeSpan.GetStop();
		m_frameTime.SetTime(0, 0, 0, 1, 0, m_pFbxScene->GetGlobalSettings().GetTimeMode());
		m_timeCount = m_start;
	}


	int meshCount = m_pFbxScene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < meshCount; i++)
	{
		//���b�V���f�[�^���擾
		FbxMesh* mesh = m_pFbxScene->GetSrcObject<FbxMesh>(i);
		std::string name = mesh->GetName();
		m_fbxMeshNameArray.push_back(name);
		m_pfbxMeshArray.push_back(mesh);

		FbxLayerElementMaterial* material = mesh->GetElementMaterial(0);
		////�e�N�X�`���̓ǂݍ���
		int textureNum = m_pFbxScene->GetSrcObjectCount<FbxFileTexture>();

		if (textureNum > 0)
		{
			//prop����FbxFileTexture���擾
			//m_fbxTextureArray.push_back(m_pFbxScene->GetSrcObject<FbxFileTexture>(i));
		}
		else
		{
		}

		//int uvLayerCount = mesh->GetElementUVCount();
		//for (int j = 0; j < uvLayerCount; j++)
		//{
		//	//UV�o�b�t�@���擾
		//	FbxGeometryElementUV* uv = mesh->GetElementUV();

		//	//�}�b�s���O���[�h�̎擾
		//	FbxGeometryElement::EMappingMode mapping = uv->GetMappingMode();
		//	//���t�@�����X���[�h�̎擾
		//	FbxGeometryElement::EReferenceMode reference = uv->GetReferenceMode();

		//	//uv�����擾
		//	int uvCount = uv->GetDirectArray().GetCount();

		//	//�}�b�s���O���[�h�̔���
		//	switch (mapping)
		//	{
		//	case fbxsdk::FbxLayerElement::eNone:
		//		break;
		//	case fbxsdk::FbxLayerElement::eByControlPoint:
		//		break;
		//	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		//		//���t�@�����X���[�h�̔���
		//		switch (reference)
		//		{
		//		case fbxsdk::FbxLayerElement::eDirect:
		//			break;
		//		case fbxsdk::FbxLayerElement::eIndex:
		//			break;
		//		case fbxsdk::FbxLayerElement::eIndexToDirect:
		//		{
		//			//FbxLayerElementArrayTemplate* uvIndex = &uv->GetIndexArray();
		//		}
		//			break;
		//		default:
		//			break;
		//		}
		//		break;
		//	case fbxsdk::FbxLayerElement::eByPolygon:
		//		break;
		//	case fbxsdk::FbxLayerElement::eByEdge:
		//		break;
		//	case fbxsdk::FbxLayerElement::eAllSame:
		//		break;
		//	default:
		//		break;
		//	}
		//}


	}

	//�e�N�X�`���̓ǂݍ���
	int layerNum = m_pFbxScene->GetSrcObjectCount<FbxFileTexture>();
	if (layerNum > 0)
	{
		for (int i = 0; i < layerNum; i++)
		{
			m_fbxTextureArray.push_back(m_pFbxScene->GetSrcObject<FbxFileTexture>(i));
			m_fbxTextureFilePath.push_back(m_fbxTextureArray[i]->GetRelativeFileName());
		}
	}



	//���X�^���C�U�̐ݒ�
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = TRUE;
	(pDevice->CreateRasterizerState(&rdc, &m_pRasterizerState));


	m_pStates = std::make_unique<DirectX::CommonStates>(m_pDevice);

	return true;
}

///////////////////////////
//�`��
//����:�f�o�C�X�A�R���e�L�X�g�A���[���h�s��A�r���[�s��A�ˉe�s��
//�߂�l:
//////////////////////////
void FbxModel::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Vector4 color)
{
	m_color = color;
	//�A�j���[�V���������邩�ǂ���
	//�A�j���[�V�����L
	if (m_isAnimation == true)
	{
		m_timeCount += m_frameTime;
		if (m_timeCount > m_stop)m_timeCount = m_start;

		this->DrawAnimation(m_pFbxScene->GetRootNode(), world, view, proj);
	}
	//�A�j���[�V������
	else
	{
		this->DrawModel(m_pFbxScene->GetRootNode(), world, view, proj);
	}

}


///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void FbxModel::ChangeAnimation(const int & animeStack)
{
	if (m_AnimStackNumber != animeStack)
	{
		FbxArray<FbxString*> animStackNameArray;
		m_AnimStackNumber = animeStack;
		m_pFbxScene->FillAnimStackNameArray(animStackNameArray);
		FbxAnimStack* animationStack = m_pFbxScene->FindMember < FbxAnimStack>(animStackNameArray[m_AnimStackNumber]->Buffer());
		m_pFbxScene->SetCurrentAnimationStack(animationStack);
		FbxTakeInfo* takeInfo = m_pFbxScene->GetTakeInfo(*(animStackNameArray[animeStack]));
		m_start = takeInfo->mLocalTimeSpan.GetStart();
		m_stop = takeInfo->mLocalTimeSpan.GetStop();
		m_frameTime.SetTime(0, 0, 0, 1, 0, m_pFbxScene->GetGlobalSettings().GetTimeMode());
		m_timeCount = m_start;
	}
}

///////////////////////////
//�A�j���[�V�����p�̕`��
//����:�m�[�h�̃|�C���^�A���[���h�s��A�r���[�s��A�ˉe�s��
//�߂�l:
//////////////////////////
bool FbxModel::DrawAnimation(FbxNode * pNode, DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//�ړ��A��]�A�g��p�̍s��쐬
	FbxMatrix globalPosition = pNode->EvaluateGlobalTransform(m_timeCount);
	FbxVector4 trans0 = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot0 = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale0 = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix geometryOffset = FbxAMatrix(trans0, rot0, scale0);

	//�p�C�v���C������
	RECT csize;
	GetClientRect(m_window, &csize);
	int cWidth = csize.right;
	int cHeight = csize.bottom;

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)cWidth;
	vp.Height = (FLOAT)cHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	m_vp = vp;

	int count = m_pfbxMeshArray.size();
	//�@�����X�g
	FbxArray<FbxVector4> normals;
	for (int i = 0; i < count; i++)
	{
		FbxMesh* mesh = m_pfbxMeshArray[i];


		Vertex* vertices = new Vertex[mesh->GetControlPointsCount()];
		mesh->GetPolygonVertexNormals(normals);

		//for (int i = 0; i < 5; i++)
		//{
		//	for (int j = 0; j < 5; j++)
		//	{
		//		double theta = DirectX::XMConvertToRadians(180.0f * i / 5);
		//		double phi = DirectX::XMConvertToRadians(360.0f * j / 5);
		//		double x = sin(theta) * cos(phi);
		//		double y = cos(theta);
		//		double z = sin(theta)* sin(phi);
		//		vertices[5 * i + j].pos = DirectX::SimpleMath::Vector3({ (float)x,(float)y,(float)z });
		//		vertices[5 * i + j].normal = DirectX::SimpleMath::Vector3({ (float)x,(float)y,(float)z });

		//	}
		//}

		//���_�o�b�t�@�쐬
		D3D11_BUFFER_DESC bdVertex;
		bdVertex.ByteWidth = sizeof(Vertex) * mesh->GetControlPointsCount();
		bdVertex.Usage = D3D11_USAGE_DYNAMIC;
		bdVertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bdVertex.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bdVertex.MiscFlags = 0;
		bdVertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA initDataIndex;
		initDataIndex.pSysMem = vertices;
		if (FAILED(m_pDevice->CreateBuffer(&bdVertex, &initDataIndex, &m_pVerBuffer)))
		{
			assert(false && "Missing");
		}

		//�C���f�b�N�X�f�[�^�̎��o���ƃo�b�t�@�̐ݒ�
		D3D11_BUFFER_DESC bdIndex;
		bdIndex.ByteWidth = sizeof(int) * mesh->GetPolygonVertexCount();
		bdIndex.Usage = D3D11_USAGE_DEFAULT;
		bdIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bdIndex.CPUAccessFlags = 0;
		bdIndex.MiscFlags = 0;
		bdIndex.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data_index;
		data_index.pSysMem = mesh->GetPolygonVertices();
		if (FAILED(m_pDevice->CreateBuffer(&bdIndex, &data_index, &m_pIndBuffer)))
		{
			assert(false && "Missing !");
		}

		//// ���X�^���C�U�̐ݒ�
		//D3D11_RASTERIZER_DESC rdc = {};
		//rdc.CullMode = D3D11_CULL_BACK;
		//rdc.FillMode = D3D11_FILL_SOLID;
		//rdc.FrontCounterClockwise = TRUE;
		//m_pDevice->CreateRasterizerState(&rdc, &m_pRasterizerState);
		
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		m_pContext->IASetVertexBuffers(0, 1, &m_pVerBuffer, &stride, &offset);
		m_pContext->IASetIndexBuffer(m_pIndBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_pContext->IASetInputLayout(m_pVertexLayout);
		m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
		m_pContext->PSSetShader(m_pPixelShader, NULL, 0);
		m_pContext->RSSetState(m_pRasterizerState);
		//m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
		m_pContext->RSSetViewports(1, &m_vp);

		//�e���_�ɂ����邽�߂̍ŏI�I�ȍs��̔z��
		FbxMatrix* clusterDeformation = new FbxMatrix[mesh->GetControlPointsCount()];
		memset(clusterDeformation, 0, sizeof(FbxMatrix) * mesh->GetControlPointsCount());

		FbxSkin* skinDeformer = (FbxSkin*)mesh->GetDeformer(0, FbxDeformer::eSkin);
		int clusterCount = skinDeformer->GetClusterCount();

		//�e�N���X�^����e���_�ɉe��x��^���邽�߂̍s��쐬
		for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
		{
			//�{�[���̎��o��
			FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
			FbxMatrix vertexTransformMatrix;
			FbxAMatrix referenceGlobalInitPosition;
			FbxAMatrix clusterGlobalInitPosition;
			FbxMatrix clusterGlobalCurrentPosition;
			FbxMatrix clusterRelativeInitPosition;
			FbxMatrix clusterRelativeCurrentPositionInverse;

			cluster->GetTransformMatrix(referenceGlobalInitPosition);
			referenceGlobalInitPosition *= geometryOffset;
			cluster->GetTransformLinkMatrix(clusterGlobalInitPosition);
			clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(m_timeCount);
			clusterRelativeInitPosition = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;
			clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;
			vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;

			//��ō�����s��Ɋe���_���̉e���x(�d��)�������Ă��ꂼ��ɉ��Z
			for (int cnt = 0; cnt < cluster->GetControlPointIndicesCount(); cnt++)
			{
				int index = cluster->GetControlPointIndices()[cnt];
				double weight = cluster->GetControlPointWeights()[cnt];
				FbxMatrix influence = vertexTransformMatrix * weight;
				clusterDeformation[index] += influence;
			}
		}

		//FbxStringList uvSetName;
		//// UVSet�̖��O���X�g���擾
		//mesh->GetUVSetNames(uvSetName);

		//FbxArray<FbxVector2> uvBuffer;

		//mesh->GetPolygonVertexUVs(uvSetName.GetStringAt(0), uvBuffer);

		//for (int j = 0; j < uvBuffer.Size(); j++)
		//{
		//	FbxVector2& uv = uvBuffer[j];

		//	vertices[i].texturePos.x = (float)uv[0];
		//	vertices[i].texturePos.y = (float)(1.0 - uv[1]);
		//}

		


		//�ŏI�I�Ȓ��_���W���v�Z��Vertex�ɕϊ�
		int count = mesh->GetControlPointsCount();
		for (int cnt = 0; cnt < count; cnt++)
		{
			FbxVector4 outVertex = clusterDeformation[cnt].MultNormalize(mesh->GetControlPointAt(cnt));
			float x = (float)outVertex[0];
			float y = (float)outVertex[1];
			float z = (float)outVertex[2];

			vertices[cnt].pos.x = x;
			vertices[cnt].pos.y = y;
			vertices[cnt].pos.z = z;

			//vertices[cnt].normal.x = x;
			//vertices[cnt].normal.y = y;
			//vertices[cnt].normal.z = z;

			//�@���ݒ�
			//m_vertices.push_back(*vertices);


			vertices[cnt].normal.x = (float)normals[cnt][0] * 50.0f;
			vertices[cnt].normal.y = (float)normals[cnt][1] * 50.0f;
			vertices[cnt].normal.z = (float)normals[cnt][2] * 50.0f;
		}


		//for (int i = 0; i < count - 1; i++)
		//{
		//	for (int j = i + 1; j < count; j++)
		//	{
		//		Vertex ver;

		//		if (vertices[i].pos.z < vertices[j].pos.z)
		//		{
		//			ver = vertices[j];
		//			vertices[i] = ver;
		//			vertices[j] = vertices[i];
		//		}
		//	}
		//}

		
		//FbxGeometryElementNormal* normal = mesh->GetElementNormal(i);
		//int normalCount = normal->GetDirectArray().GetCount();
		//for (int cnt = 0; cnt < normalCount; cnt++)
		//{
		//	m_vertices.push_back(*vertices);
		//	m_vertices[cnt].normal.x = (float)normal->GetDirectArray().GetAt(cnt)[0];
		//	m_vertices[cnt].normal.y = (float)normal->GetDirectArray().GetAt(cnt)[1];
		//	m_vertices[cnt].normal.z = (float)normal->GetDirectArray().GetAt(cnt)[2];
		//}

		//�|���S�����̎擾
		//int polygonCount = mesh->GetPolygonCount();
		
		//�|���S���̐������A�ԂƂ��ĕۑ�����

		delete[] clusterDeformation;

		//////////////////////////
		D3D11_MAPPED_SUBRESOURCE pData;
		ConstantBuffer cb;

		//�p�����[�^�̎󂯓n��(�萔)
		cb.mW = XMMatrixTranspose(world);
		cb.mWVP = DirectX::XMMatrixTranspose(world* view* proj);
		cb.color = m_color;
		cb.lightPos = DirectX::XMVectorSet(-5, 5, -3, 1);
		cb.eyePos = DirectX::XMVectorSet(0, 0, 5.0f, 1.0f);
		m_pContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pContext->Unmap(m_pConstantBuffer, 0);

		int controlPoinsCount = mesh->GetControlPointsCount();

		//�p�����[�^�̎󂯓n��(���_)
		m_pContext->Map(m_pVerBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		memcpy_s(pData.pData, pData.RowPitch, (void*)(vertices), sizeof(Vertex)*controlPoinsCount);
		m_pContext->Unmap(m_pVerBuffer, 0);


		//�`����s
		int polygonVertexCount = mesh->GetPolygonVertexCount();
		m_pContext->DrawIndexed(polygonVertexCount, 0, 0);
		//m_pSwapChain->Present(0, 0);

		delete[] vertices;
		m_pVerBuffer->Release();
		m_pVerBuffer = nullptr;
		m_pIndBuffer->Release();
		m_pIndBuffer = nullptr;

	}

	m_pContext->VSSetShader(nullptr, nullptr, 0);
	m_pContext->GSSetShader(nullptr, nullptr, 0);
	m_pContext->PSSetShader(nullptr, nullptr, 0);

	return true;
}

///////////////////////////
//�ʏ�̕`��
//����:�m�[�h�̃|�C���^�A���[���h�s��A�r���[�s��A�ˉe�s��
//�߂�l:
//////////////////////////
bool FbxModel::DrawModel(FbxNode * pNode, DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	int count = m_pfbxMeshArray.size();

	//�@�����X�g
	FbxArray<FbxVector4> normals;
	for (int i = 0; i < count; i++)
	{
		FbxMesh* mesh = m_pfbxMeshArray[i];

		Vertex*vertices = new Vertex[mesh->GetControlPointsCount()];

		mesh->GetPolygonVertexNormals(normals);

		for (int cnt = 0; cnt < mesh->GetControlPointsCount(); cnt++)
		{
			float x = (float)mesh->GetControlPointAt(cnt)[0];
			float y = (float)mesh->GetControlPointAt(cnt)[1];
			float z = (float)mesh->GetControlPointAt(cnt)[2];

			vertices[cnt].pos.x = x;
			vertices[cnt].pos.y = y;
			vertices[cnt].pos.z = z;

			vertices[cnt].normal.x = (float)normals[cnt][0] * 50.0f;
			vertices[cnt].normal.y = (float)normals[cnt][1] * 50.0f;
			vertices[cnt].normal.z = (float)normals[cnt][2] * 50.0f;

		}
		D3D11_BUFFER_DESC bdVertex;
		bdVertex.ByteWidth = sizeof(Vertex) * mesh->GetControlPointsCount();
		bdVertex.Usage = D3D11_USAGE_DYNAMIC;
		bdVertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bdVertex.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bdVertex.MiscFlags = 0;
		bdVertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA initDataIndex;
		initDataIndex.pSysMem = vertices;

		if (FAILED(m_pDevice->CreateBuffer(&bdVertex, &initDataIndex, &m_pVerBuffer)))
		{
			assert(false && "Missing");
		}

		//�C���f�b�N�X�f�[�^�̎��o���ƃo�b�t�@�̐ݒ�
		D3D11_BUFFER_DESC bdIndex;
		bdIndex.ByteWidth = sizeof(int) * mesh->GetPolygonVertexCount();
		bdIndex.Usage = D3D11_USAGE_DEFAULT;
		bdIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bdIndex.CPUAccessFlags = 0;
		bdIndex.MiscFlags = 0;
		bdIndex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA dataIndex;
		dataIndex.pSysMem = mesh->GetPolygonVertices();
		if (FAILED(m_pDevice->CreateBuffer(&bdIndex, &dataIndex, &m_pIndBuffer)))
		{
			assert(false && "Missing");
		}

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		m_pContext->IASetVertexBuffers(0, 1, &m_pVerBuffer, &stride, &offset);
		m_pContext->IASetIndexBuffer(m_pIndBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_pContext->IASetInputLayout(m_pVertexLayout);
		m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
		m_pContext->PSSetShader(m_pPixelShader, NULL, 0);
		m_pContext->RSSetState(m_pRasterizerState);
		//m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
		m_pContext->RSSetViewports(1, &m_vp);

		D3D11_MAPPED_SUBRESOURCE pData;
		ConstantBuffer cb;

		//�p�����[�^�̎󂯓n��(�萔)
		cb.mW = XMMatrixTranspose(world);
		cb.mWVP = DirectX::XMMatrixTranspose(world* view* proj);
		cb.color = m_color;
		cb.lightPos = DirectX::XMVectorSet(-5, 5, -3, 1);
		cb.eyePos = DirectX::XMVectorSet(0, 0, 5.0f, 1.0f);
		cb.mWVP = DirectX::XMMatrixTranspose(world * view * proj);
		m_pContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pContext->Unmap(m_pConstantBuffer, 0);

		int controlPointsCount = mesh->GetControlPointsCount();

		//�p�����[�^�̎󂯓n��(���_)
		m_pContext->Map(m_pVerBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		memcpy_s(pData.pData, pData.RowPitch, (void*)(vertices), sizeof(Vertex)* controlPointsCount);
		m_pContext->Unmap(m_pVerBuffer, 0);

		//�`����s
		int polygonVertexCount = mesh->GetPolygonVertexCount();
		m_pContext->DrawIndexed(polygonVertexCount, 0, 0);

		delete[] vertices;
		m_pVerBuffer->Release();
		m_pVerBuffer = nullptr;
		m_pIndBuffer->Release();
		m_pIndBuffer = nullptr;

	}
	return true;
}
