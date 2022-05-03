//グローバル定数　唯一、ｃ＋＋側からデータを入れることができる所
float4x4 mW;//ワールド行列（キャラの行列）
float4x4 mV;//ビュー行列（カメラ）
float4x4 mP;//射影（2D）変換行列

//輪郭用データーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
float4 OutlineColor = float4(0, 0, 0, 0);;	//輪郭色
float OutlineSize = float(1);		//輪郭の太さ//
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//環境マッピング用
//---------------------------------------------------------------------------------------------------------
float RefPower = 0.5;//映り込み率
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
//マテリアル関係
//-----------------------------------------------------------------------------------------------------------
float4 MateSpecular = float4(1, 1, 1, 1);		//反射色
float MateSpePower = 50;						//反射の鋭さ
float4 MateDiffuse = float4(1, 1, 1, 1);		//マテリアル色
texture MateDiffuseTex;							//マテリアルのテクスチャ

//MateDiffuseTex用サンプラ
sampler MateDiffuseSmp = sampler_state {
	Texture = <MateDiffuseTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR; //フィルタ
	MagFilter = LINEAR;
	AddressU = Wrap;//テクスチャ　アドレシングモード
	AddressV = Wrap;
};
//----------------------------------------------------------------------------------------------------------
//ライト関係
//--------------------------------------------------------------------------------------------------------
float4 LightColor = float4(1, 1, 1, 1);
float3 LightDir = float3(0, -1, 0);				//平行光の方向
float4 LightAmbient;							//環境光　絶対に当たる光
float4 LightSpecular = float4(1, 1, 1, 1);		//反射の色
												//----------------------------------------------------------------------------------------------------------
//カメラ関係
//--------------------------------------------------------------------------------------------------------
float3 CamPos;								//カメラ座標

//頂点シェーダ出力用構造体　　　頂点シェーダ　頂点座標を2dに
struct VS_OUT {
	float4 Pos		: POSITION;		//射影（２ｄ）座標　セマンティクス　
	float3 wN       : TEXCOORD0;    //ワールド法線
	float2 MeshUV	: TEXCOORD1;	//UV座標
	float3 wPos		: TEXCOORD2;	//3D座標

};

//頂点シェーダ
VS_OUT VS(float4 Pos	 :	POSITION,
		  float3 normal  :  NORMAL,		//法線ベクトル
		  float2 mesh_uv :  TEXCOORD0)	//UV座標
{
	VS_OUT Out;
	Out.Pos = mul(Pos, mW);			//３Dへ
	Out.wPos = Out.Pos.xyz;
	Out.Pos = mul(Out.Pos, mV);
	Out.Pos = mul(Out.Pos, mP);
	Out.wN = mul(normal, (float3x3)mW);
	Out.wN = normalize(Out.wN);
	Out.MeshUV = mesh_uv;
	return Out;

}
//ピクセルシェーダ出力用構造体
struct PS_OUT
{
	float4 Color : COLOR0;  // 出力色(RenderTargetの0番目に出力する)
};
PS_OUT PS(VS_OUT In)
{
	//法線を初期化
	float3 w_normal = normalize(In.wN);
	float3 vCam = normalize(CamPos - In.wPos);		//カメラの方向

													//--------------------------------------
													//モデル色
													//--------------------------------------
	float4 texCol = tex2D(MateDiffuseSmp, In.MeshUV);
	float4 modelCol = MateDiffuse*texCol;

	//--------------------------------------
	//ライト色
	//--------------------------------------
	float4 lightCol = float4(0, 0, 0, 1);
	//平行光ライティング（ランバート）
	float LPow = dot(-LightDir, w_normal);
	LPow = saturate(LPow);
	//ToonTexから色を取得
	/*float4 toonCol = tex2D(ToonSmp, float2(LPow, 0));*/
	lightCol += LightColor*LPow;

	//環境光
	lightCol += LightAmbient;

	//反射光
	float4 lightSpe = 0;
	float3 vRef = reflect(LightDir, w_normal);
	float SPow = dot(vCam, vRef);		//-1~1
	SPow = saturate(SPow);				//0~1
	SPow = pow(SPow, MateSpePower);
	lightSpe += LightSpecular * SPow;

	//--------------------------------------
	//色を出力
	//--------------------------------------
	float4 diffuseCol = modelCol * lightCol;//拡散色
	float4 speCol = lightSpe * MateSpecular;
	PS_OUT Out;
	Out.Color = diffuseCol;
	Out.Color.rgb += speCol.rgb;
	return Out;

}
//テクニック
technique Tech {
	pass P0 {
		VertexShader = compile vs_3_0 VS();   // 頂点シェーダはVS()を使う
		PixelShader = compile ps_3_0 PS();    // ピクセルシェーダはPS()を使う
	}
}
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//輪郭シェーダ
//---------------------------------------------------------------------------------
struct OutlineVS_OUT {//頂点シェーダ出力用構造体　
	float4 Pos		: POSITION;//射影（２ｄ）座標　セマンティクス
};
//vs
OutlineVS_OUT OutlineVS(float4 pos:POSITION, float3 normal : NORMAL) {
	OutlineVS_OUT Outline;
	//pos + e normal方向にずらす
	pos.xyz += normal*OutlineSize;//error
	//2D(射影）へ
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
	float4 Color : COLOR0;  // 出力色(RenderTargetの0番目に出力する)
};
OutlinePS_OUT OutlinePS(OutlineVS_OUT In)
{
	OutlinePS_OUT Outline;
	Outline.Color = OutlineColor;
	return Outline;
}
//テクニック
technique OutlineTech {
	pass pa {
		VertexShader = compile vs_3_0 OutlineVS();
		PixelShader = compile ps_3_0 OutlinePS();
		CullMode = CW;		//カリングモードをCWに（裏面描画）
	}
};