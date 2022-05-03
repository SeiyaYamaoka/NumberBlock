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
 28;
 -10.00000;1.00000;10.00000;,
 10.00000;1.00000;10.00000;,
 10.00000;1.00000;-10.00000;,
 -10.00000;1.00000;-10.00000;,
 -10.00000;-1.00000;-10.00000;,
 10.00000;-1.00000;-10.00000;,
 10.00000;-1.00000;10.00000;,
 -10.00000;-1.00000;10.00000;,
 10.00000;0.29803;-10.00000;,
 10.00000;-1.00000;-10.00000;,
 -10.00000;-1.00000;-10.00000;,
 -10.00000;0.29803;-10.00000;,
 -10.00000;1.00000;-10.00000;,
 10.00000;1.00000;-10.00000;,
 10.00000;0.34061;10.00000;,
 10.00000;-1.00000;-10.00000;,
 10.00000;0.29803;-10.00000;,
 10.00000;1.00000;-10.00000;,
 -10.00000;0.34061;10.00000;,
 -10.00000;-1.00000;10.00000;,
 10.00000;-1.00000;10.00000;,
 10.00000;0.34061;10.00000;,
 10.00000;1.00000;10.00000;,
 -10.00000;1.00000;10.00000;,
 -10.00000;0.29803;-10.00000;,
 -10.00000;-1.00000;-10.00000;,
 -10.00000;0.34061;10.00000;,
 -10.00000;1.00000;-10.00000;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,12,13,8;,
 4;14,6,15,16;,
 4;16,17,1,14;,
 4;18,19,20,21;,
 4;21,22,23,18;,
 4;24,25,7,26;,
 4;26,0,27,24;;
 
 MeshMaterialList {
  2;
  10;
  1,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\yanoka\\Downloads\\photo0000-0169.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\yanoka\\Downloads\\photo0000-0375.jpg";
   }
  }
 }
 MeshNormals {
  12;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;-0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000001;0.000000;,
  0.000000;0.000001;1.000000;,
  0.000000;-0.000002;1.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000001;0.000000;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,5,5,3;,
  4;3,6,6,3;,
  4;4,7,7,4;,
  4;4,8,8,4;,
  4;9,10,10,9;,
  4;9,11,11,9;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  1.000000;0.350984;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.350984;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.329696;
  0.000000;1.000000;
  0.000000;0.350984;
  0.000000;0.000000;
  1.000000;0.329696;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.329696;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.350984;
  1.000000;1.000000;
  0.000000;0.329696;
  1.000000;0.000000;;
 }
}
