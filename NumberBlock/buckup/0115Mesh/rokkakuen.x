xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 102;
 0.00000;5.00000;-5.00000;,
 0.62667;5.00000;-4.96057;,
 0.62667;-5.00000;-4.96057;,
 0.00000;-5.00000;-5.00000;,
 1.24345;5.00000;-4.84292;,
 1.24345;-5.00000;-4.84292;,
 1.84062;5.00000;-4.64888;,
 1.84062;-5.00000;-4.64888;,
 2.40877;5.00000;-4.38153;,
 2.40877;-5.00000;-4.38153;,
 2.93893;5.00000;-4.04508;,
 2.93893;-5.00000;-4.04508;,
 3.42274;5.00000;-3.64484;,
 3.42274;-5.00000;-3.64484;,
 3.85257;5.00000;-3.18712;,
 3.85257;-5.00000;-3.18712;,
 4.22164;5.00000;-2.67913;,
 4.22164;-5.00000;-2.67913;,
 4.52414;5.00000;-2.12890;,
 4.52414;-5.00000;-2.12890;,
 4.75528;5.00000;-1.54508;,
 4.75528;-5.00000;-1.54508;,
 4.91144;5.00000;-0.93691;,
 4.91144;-5.00000;-0.93691;,
 4.99013;5.00000;-0.31395;,
 4.99013;-5.00000;-0.31395;,
 4.99013;5.00000;0.31395;,
 4.99013;-5.00000;0.31395;,
 4.91144;5.00000;0.93691;,
 4.91144;-5.00000;0.93691;,
 4.75528;5.00000;1.54508;,
 4.75528;-5.00000;1.54508;,
 4.52414;5.00000;2.12890;,
 4.52414;-5.00000;2.12890;,
 4.22164;5.00000;2.67913;,
 4.22164;-5.00000;2.67913;,
 3.85257;5.00000;3.18712;,
 3.85257;-5.00000;3.18712;,
 3.42274;5.00000;3.64484;,
 3.42274;-5.00000;3.64484;,
 2.93893;5.00000;4.04508;,
 2.93893;-5.00000;4.04508;,
 2.40877;5.00000;4.38153;,
 2.40877;-5.00000;4.38153;,
 1.84062;5.00000;4.64888;,
 1.84062;-5.00000;4.64888;,
 1.24345;5.00000;4.84292;,
 1.24345;-5.00000;4.84292;,
 0.62667;5.00000;4.96057;,
 0.62667;-5.00000;4.96057;,
 0.00000;5.00000;5.00000;,
 0.00000;-5.00000;5.00000;,
 -0.62667;5.00000;4.96057;,
 -0.62667;-5.00000;4.96057;,
 -1.24345;5.00000;4.84292;,
 -1.24345;-5.00000;4.84292;,
 -1.84062;5.00000;4.64888;,
 -1.84062;-5.00000;4.64888;,
 -2.40877;5.00000;4.38153;,
 -2.40877;-5.00000;4.38153;,
 -2.93893;5.00000;4.04508;,
 -2.93893;-5.00000;4.04508;,
 -3.42274;5.00000;3.64484;,
 -3.42274;-5.00000;3.64484;,
 -3.85257;5.00000;3.18712;,
 -3.85257;-5.00000;3.18712;,
 -4.22164;5.00000;2.67913;,
 -4.22164;-5.00000;2.67913;,
 -4.52414;5.00000;2.12890;,
 -4.52414;-5.00000;2.12890;,
 -4.75528;5.00000;1.54508;,
 -4.75528;-5.00000;1.54508;,
 -4.91144;5.00000;0.93691;,
 -4.91144;-5.00000;0.93691;,
 -4.99013;5.00000;0.31395;,
 -4.99013;-5.00000;0.31395;,
 -4.99013;5.00000;-0.31395;,
 -4.99013;-5.00000;-0.31395;,
 -4.91144;5.00000;-0.93691;,
 -4.91144;-5.00000;-0.93691;,
 -4.75528;5.00000;-1.54508;,
 -4.75528;-5.00000;-1.54508;,
 -4.52414;5.00000;-2.12890;,
 -4.52414;-5.00000;-2.12890;,
 -4.22164;5.00000;-2.67913;,
 -4.22164;-5.00000;-2.67913;,
 -3.85257;5.00000;-3.18712;,
 -3.85257;-5.00000;-3.18712;,
 -3.42274;5.00000;-3.64484;,
 -3.42274;-5.00000;-3.64484;,
 -2.93893;5.00000;-4.04508;,
 -2.93893;-5.00000;-4.04508;,
 -2.40877;5.00000;-4.38153;,
 -2.40877;-5.00000;-4.38153;,
 -1.84062;5.00000;-4.64888;,
 -1.84062;-5.00000;-4.64888;,
 -1.24345;5.00000;-4.84292;,
 -1.24345;-5.00000;-4.84292;,
 -0.62667;5.00000;-4.96057;,
 -0.62667;-5.00000;-4.96057;,
 0.00000;5.00000;-5.00000;,
 0.00000;-5.00000;-5.00000;;
 
 50;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;;
 
 MeshMaterialList {
  1;
  50;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\yanoka\\Pictures\\rokkaku.png";
   }
  }
 }
 MeshNormals {
  50;
  0.000000;0.000000;-1.000000;,
  0.125333;0.000000;-0.992115;,
  0.248690;0.000000;-0.968583;,
  0.368125;0.000000;-0.929776;,
  0.481754;0.000000;-0.876307;,
  0.587785;0.000000;-0.809017;,
  0.684547;0.000000;-0.728969;,
  0.770513;0.000000;-0.637424;,
  0.844328;0.000000;-0.535827;,
  0.904827;0.000000;-0.425779;,
  0.951056;0.000000;-0.309017;,
  0.982287;0.000000;-0.187381;,
  0.998027;0.000000;-0.062791;,
  0.998027;0.000000;0.062791;,
  0.982287;0.000000;0.187381;,
  0.951056;0.000000;0.309017;,
  0.904827;0.000000;0.425779;,
  0.844328;0.000000;0.535827;,
  0.770513;0.000000;0.637424;,
  0.684547;0.000000;0.728969;,
  0.587785;0.000000;0.809017;,
  0.481754;0.000000;0.876307;,
  0.368125;0.000000;0.929776;,
  0.248690;0.000000;0.968583;,
  0.125333;0.000000;0.992115;,
  0.000000;0.000000;1.000000;,
  -0.125333;0.000000;0.992115;,
  -0.248690;0.000000;0.968583;,
  -0.368125;0.000000;0.929776;,
  -0.481754;0.000000;0.876307;,
  -0.587785;0.000000;0.809017;,
  -0.684547;0.000000;0.728969;,
  -0.770513;0.000000;0.637424;,
  -0.844328;0.000000;0.535827;,
  -0.904827;0.000000;0.425779;,
  -0.951056;0.000000;0.309017;,
  -0.982287;0.000000;0.187381;,
  -0.998027;0.000000;0.062791;,
  -0.998027;0.000000;-0.062791;,
  -0.982287;0.000000;-0.187381;,
  -0.951056;0.000000;-0.309017;,
  -0.904827;0.000000;-0.425779;,
  -0.844328;0.000000;-0.535827;,
  -0.770513;0.000000;-0.637424;,
  -0.684547;0.000000;-0.728969;,
  -0.587785;0.000000;-0.809017;,
  -0.481754;0.000000;-0.876307;,
  -0.368125;0.000000;-0.929776;,
  -0.248690;0.000000;-0.968583;,
  -0.125333;0.000000;-0.992115;;
  50;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,0,0,49;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.250000;
  0.020039;0.250005;
  0.020039;0.749995;
  0.000000;0.750000;
  0.040076;0.250019;
  0.040076;0.749980;
  0.060108;0.250043;
  0.060108;0.749957;
  0.080133;0.250073;
  0.080133;0.749927;
  0.100150;0.250109;
  0.100150;0.749891;
  0.120157;0.250147;
  0.120157;0.749853;
  0.140154;0.250187;
  0.140154;0.749813;
  0.160142;0.250224;
  0.160142;0.749776;
  0.180121;0.250257;
  0.180121;0.749743;
  0.200092;0.250284;
  0.200092;0.749716;
  0.220058;0.250303;
  0.220058;0.749697;
  0.240020;0.250313;
  0.240020;0.749687;
  0.259980;0.250313;
  0.259980;0.749687;
  0.279942;0.250303;
  0.279942;0.749697;
  0.299908;0.250284;
  0.299908;0.749716;
  0.319879;0.250257;
  0.319879;0.749743;
  0.339858;0.250224;
  0.339858;0.749776;
  0.359846;0.250187;
  0.359846;0.749813;
  0.379843;0.250147;
  0.379843;0.749853;
  0.399850;0.250109;
  0.399850;0.749891;
  0.419867;0.250073;
  0.419867;0.749927;
  0.439892;0.250043;
  0.439892;0.749957;
  0.459924;0.250019;
  0.459924;0.749980;
  0.479961;0.250005;
  0.479961;0.749995;
  0.500000;0.250000;
  0.500000;0.750000;
  0.520039;0.250005;
  0.520039;0.749995;
  0.540076;0.250019;
  0.540076;0.749980;
  0.560108;0.250043;
  0.560108;0.749957;
  0.580133;0.250073;
  0.580133;0.749927;
  0.600150;0.250109;
  0.600150;0.749891;
  0.620157;0.250147;
  0.620157;0.749853;
  0.640154;0.250187;
  0.640154;0.749813;
  0.660142;0.250224;
  0.660142;0.749776;
  0.680121;0.250257;
  0.680121;0.749743;
  0.700092;0.250284;
  0.700092;0.749716;
  0.720058;0.250303;
  0.720058;0.749697;
  0.740020;0.250313;
  0.740020;0.749687;
  0.759980;0.250313;
  0.759980;0.749687;
  0.779942;0.250303;
  0.779942;0.749697;
  0.799908;0.250284;
  0.799908;0.749716;
  0.819879;0.250257;
  0.819879;0.749743;
  0.839858;0.250224;
  0.839858;0.749776;
  0.859846;0.250187;
  0.859846;0.749813;
  0.879843;0.250147;
  0.879843;0.749853;
  0.899850;0.250109;
  0.899850;0.749891;
  0.919867;0.250073;
  0.919867;0.749927;
  0.939892;0.250043;
  0.939892;0.749957;
  0.959924;0.250019;
  0.959924;0.749980;
  0.979961;0.250005;
  0.979961;0.749995;
  1.000000;0.250000;
  1.000000;0.750000;;
 }
}