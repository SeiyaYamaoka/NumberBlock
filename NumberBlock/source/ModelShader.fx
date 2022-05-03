//�O���[�o���萔�@�B��A���{�{������f�[�^�����邱�Ƃ��ł��鏊
float4x4 mW;//���[���h�s��i�L�����̍s��j
float4x4 mV;//�r���[�s��i�J�����j
float4x4 mP;//�ˉe�i2D�j�ϊ��s��

//�֊s�p�f�[�^�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
float4 OutlineColor = float4(0, 0, 0, 0);;	//�֊s�F
float OutlineSize = float(1);		//�֊s�̑���//
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//���}�b�s���O�p
//---------------------------------------------------------------------------------------------------------
float RefPower = 0.5;//�f�荞�ݗ�
texture CubeTex;
samplerCUBE CubeSmp = sampler_state {
	Texture = <CubeTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
//-----------------------------------------------------------------------------------------------------------
//�}�e���A���֌W
//-----------------------------------------------------------------------------------------------------------
float4 MateSpecular = float4(1, 1, 1, 1);		//���ːF
float MateSpePower = 50;						//���˂̉s��
float4 MateDiffuse = float4(1, 1, 1, 1);		//�}�e���A���F
texture MateDiffuseTex;							//�}�e���A���̃e�N�X�`��

//MateDiffuseTex�p�T���v��
sampler MateDiffuseSmp = sampler_state {
	Texture = <MateDiffuseTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR; //�t�B���^
	MagFilter = LINEAR;
	AddressU = Wrap;//�e�N�X�`���@�A�h���V���O���[�h
	AddressV = Wrap;
};
//----------------------------------------------------------------------------------------------------------
//���C�g�֌W
//--------------------------------------------------------------------------------------------------------
float4 LightColor = float4(1, 1, 1, 1);
float3 LightDir = float3(0, -1, 0);				//���s���̕���
float4 LightAmbient;							//�����@��΂ɓ������
float4 LightSpecular = float4(1, 1, 1, 1);		//���˂̐F
												//----------------------------------------------------------------------------------------------------------
//�J�����֌W
//--------------------------------------------------------------------------------------------------------
float3 CamPos;								//�J�������W

//���_�V�F�[�_�o�͗p�\���́@�@�@���_�V�F�[�_�@���_���W��2d��
struct VS_OUT {
	float4 Pos		: POSITION;		//�ˉe�i�Q���j���W�@�Z�}���e�B�N�X�@
	float3 wN       : TEXCOORD0;    //���[���h�@��
	float2 MeshUV	: TEXCOORD1;	//UV���W
	float3 wPos		: TEXCOORD2;	//3D���W

};

//���_�V�F�[�_
VS_OUT VS(float4 Pos	 :	POSITION,
		  float3 normal  :  NORMAL,		//�@���x�N�g��
		  float2 mesh_uv :  TEXCOORD0)	//UV���W
{
	VS_OUT Out;
	Out.Pos = mul(Pos, mW);			//�RD��
	Out.wPos = Out.Pos.xyz;
	Out.Pos = mul(Out.Pos, mV);
	Out.Pos = mul(Out.Pos, mP);
	Out.wN = mul(normal, (float3x3)mW);
	Out.wN = normalize(Out.wN);
	Out.MeshUV = mesh_uv;
	return Out;

}
//�s�N�Z���V�F�[�_�o�͗p�\����
struct PS_OUT
{
	float4 Color : COLOR0;  // �o�͐F(RenderTarget��0�Ԗڂɏo�͂���)
};
PS_OUT PS(VS_OUT In)
{
	//�@����������
	float3 w_normal = normalize(In.wN);
	float3 vCam = normalize(CamPos - In.wPos);		//�J�����̕���

													//--------------------------------------
													//���f���F
													//--------------------------------------
	float4 texCol = tex2D(MateDiffuseSmp, In.MeshUV);
	float4 modelCol = MateDiffuse*texCol;

	//--------------------------------------
	//���C�g�F
	//--------------------------------------
	float4 lightCol = float4(0, 0, 0, 1);
	//���s�����C�e�B���O�i�����o�[�g�j
	float LPow = dot(-LightDir, w_normal);
	LPow = saturate(LPow);
	//ToonTex����F���擾
	/*float4 toonCol = tex2D(ToonSmp, float2(LPow, 0));*/
	lightCol += LightColor*LPow;

	//����
	lightCol += LightAmbient;

	//���ˌ�
	float4 lightSpe = 0;
	float3 vRef = reflect(LightDir, w_normal);
	float SPow = dot(vCam, vRef);		//-1~1
	SPow = saturate(SPow);				//0~1
	SPow = pow(SPow, MateSpePower);
	lightSpe += LightSpecular * SPow;

	//--------------------------------------
	//�F���o��
	//--------------------------------------
	float4 diffuseCol = modelCol * lightCol;//�g�U�F
	float4 speCol = lightSpe * MateSpecular;
	PS_OUT Out;
	Out.Color = diffuseCol;
	Out.Color.rgb += speCol.rgb;
	return Out;

}
//�e�N�j�b�N
technique Tech {
	pass P0 {
		VertexShader = compile vs_3_0 VS();   // ���_�V�F�[�_��VS()���g��
		PixelShader = compile ps_3_0 PS();    // �s�N�Z���V�F�[�_��PS()���g��
	}
}
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�֊s�V�F�[�_
//---------------------------------------------------------------------------------
struct OutlineVS_OUT {//���_�V�F�[�_�o�͗p�\���́@
	float4 Pos		: POSITION;//�ˉe�i�Q���j���W�@�Z�}���e�B�N�X
};
//vs
OutlineVS_OUT OutlineVS(float4 pos:POSITION, float3 normal : NORMAL) {
	OutlineVS_OUT Outline;
	//pos + e normal�����ɂ��炷
	pos.xyz += normal*OutlineSize;//error
	//2D(�ˉe�j��
	Outline.Pos = mul(pos, mW);		
	Outline.Pos = mul(Outline.Pos, mV);
	Outline.Pos = mul(Outline.Pos, mP);
	return Outline;
}
//ps
//float4 OutlinePS(OutlineVS_OUT In):COLOR0 {
//	return OutlineColor;
//}
struct OutlinePS_OUT
{
	float4 Color : COLOR0;  // �o�͐F(RenderTarget��0�Ԗڂɏo�͂���)
};
OutlinePS_OUT OutlinePS(OutlineVS_OUT In)
{
	OutlinePS_OUT Outline;
	Outline.Color = OutlineColor;
	return Outline;
}
//�e�N�j�b�N
technique OutlineTech {
	pass pa {
		VertexShader = compile vs_3_0 OutlineVS();
		PixelShader = compile ps_3_0 OutlinePS();
		CullMode = CW;		//�J�����O���[�h��CW�Ɂi���ʕ`��j
	}
};