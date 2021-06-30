//// 定数バッファ(CPU側からの値受け取り場)
//cbuffer global {
//	matrix gWVP;    // 変換行列
//};
// 
//// 頂点シェーダ
//float4 VS(float4 Pos : POSITION) : SV_POSITION
//{
//
//	return mul(Pos,gWVP);
//}
// 
//// ピクセルシェーダ
//float4 PS(float4 Pos : SV_POSITION) : SV_Target
//{
//	float4 color = float4(-1.0f,1.0f,1.0f,1.0f);
//
//	return float4(color);
//}

// 定数バッファ(CPU側からの値受け取り場)
cbuffer global 
{
	matrix gW;
	matrix gWVP;
	float4 gLightPos;
	float4 gEyePos;
	float4 gColor;
	float2 gTexture;
};

// 頂点シェーダから出力される構造体
struct VS_OUTPUT 
{
	float4 VerPos : SV_POSITION;
	float4 LightPos : TEXCOORD0;
	float4 Normal : TEXCOORD1;
	float4 EyePos : TEXCOORD2;
	float2 Texture : TEXTURE0;
};

// 頂点シェーダ
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL, float Tex : TEXTURE)
{

	VS_OUTPUT output;
	output.VerPos = mul(Pos, gWVP);
	output.Normal = mul(Normal, gW);
	output.LightPos = gLightPos;
	output.EyePos = gEyePos;
	output.Texture = Tex;

	return output;
}

// ピクセルシェーダ
float4 PS(VS_OUTPUT input) : SV_Target {
 
	float4 L = normalize(input.LightPos - input.Normal);            // 物体表面上の点から光源への方向ベクトル
	float4 N = normalize(input.Normal);                             // 表面上の点における法線
	float LN = dot(L, N);
	float4 R = normalize(2  * N - normalize(input.LightPos));   // 光線が反射される方向
	float4 V = normalize(input.EyePos);                             // 視点に向かう方向
	float RV = saturate(dot(R, V));
 
	// 環境反射光
	float4 ambient = float4(gColor.x * 0.8, gColor.y * 0.8, gColor.z * 0.8, gColor.w);
	// 拡散反射光
	float4 diffuse = saturate(LN * gColor);
	// 鏡面反射光
	float4 specular = saturate(2.0 * pow(RV, 5.0) * float4(1.0, 1.0, 1.0, 0.1));
 
	return ambient + diffuse + specular;

	//return float4(0.5, 0.5, 1.0, 1.0);
}