//// �萔�o�b�t�@(CPU������̒l�󂯎���)
//cbuffer global {
//	matrix gWVP;    // �ϊ��s��
//};
// 
//// ���_�V�F�[�_
//float4 VS(float4 Pos : POSITION) : SV_POSITION
//{
//
//	return mul(Pos,gWVP);
//}
// 
//// �s�N�Z���V�F�[�_
//float4 PS(float4 Pos : SV_POSITION) : SV_Target
//{
//	float4 color = float4(-1.0f,1.0f,1.0f,1.0f);
//
//	return float4(color);
//}

// �萔�o�b�t�@(CPU������̒l�󂯎���)
cbuffer global 
{
	matrix gW;
	matrix gWVP;
	float4 gLightPos;
	float4 gEyePos;
	float4 gColor;
	float2 gTexture;
};

// ���_�V�F�[�_����o�͂����\����
struct VS_OUTPUT 
{
	float4 VerPos : SV_POSITION;
	float4 LightPos : TEXCOORD0;
	float4 Normal : TEXCOORD1;
	float4 EyePos : TEXCOORD2;
	float2 Texture : TEXTURE0;
};

// ���_�V�F�[�_
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

// �s�N�Z���V�F�[�_
float4 PS(VS_OUTPUT input) : SV_Target {
 
	float4 L = normalize(input.LightPos - input.Normal);            // ���̕\�ʏ�̓_��������ւ̕����x�N�g��
	float4 N = normalize(input.Normal);                             // �\�ʏ�̓_�ɂ�����@��
	float LN = dot(L, N);
	float4 R = normalize(2  * N - normalize(input.LightPos));   // ���������˂�������
	float4 V = normalize(input.EyePos);                             // ���_�Ɍ���������
	float RV = saturate(dot(R, V));
 
	// �����ˌ�
	float4 ambient = float4(gColor.x * 0.8, gColor.y * 0.8, gColor.z * 0.8, gColor.w);
	// �g�U���ˌ�
	float4 diffuse = saturate(LN * gColor);
	// ���ʔ��ˌ�
	float4 specular = saturate(2.0 * pow(RV, 5.0) * float4(1.0, 1.0, 1.0, 0.1));
 
	return ambient + diffuse + specular;

	//return float4(0.5, 0.5, 1.0, 1.0);
}