////////////////////////////////////
// Include
////////////////////////////////////
#include <WICTextureLoader.h>
#include <cstdio>

#include "texture.h"
#include "direct3d.h"
#include "error.h"

////////////////////////////////////
// �ǂݍ���
////////////////////////////////////
ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName )
{
    ID3D11ShaderResourceView* texture;

    // �e�N�X�`���̓ǂݍ���
    if( FAILED( CreateWICTextureFromFileEx(     // bmp,jpg,png�����̊֐��œǂݍ��߂�
        Direct3D::getDevice(),      // D3D�f�o�C�X�C���^�[�t�F�C�X
        Direct3D::getContext(),     // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
        FileName,                   // �t�@�C����(���C�h�����Ŏw��)
        0,                          // �~�b�v�}�b�v���x��
        D3D11_USAGE_DEFAULT,        // �g�p���@
        D3D11_BIND_SHADER_RESOURCE, // �o�C���h�̎��
        0,                          // CUP�A�N�Z�X���@
        0,                          // �t���O�I�v�V����
        WIC_LOADER_DEFAULT,         // SRGB�t���O
        NULL,                       // ���\�[�X�f�[�^����|�C���^
        &texture ) ) )              // �V�F�[�_�[���\�[�X�r���[����|�C���^
    {
        // �G���[
        char file_name[ 256 ], str[ 256 ];                              // �t�@�C���l�[���i�[�p�ϐ�file_name�ƕ�����i�[�p�ϐ�str
        wcstombs( file_name, FileName, 256 );                           // Unicode�������}���`�o�C�g�����ɕϊ�
        sprintf( str, "�e�N�X�`���̓ǂݍ��݂Ɏ��s(%s)", file_name );    // str�ɕ������i�[
        Error::showDialog( str );                                       // �G���[���b�Z�[�W�\��

        return NULL;
    }

    return texture;
}