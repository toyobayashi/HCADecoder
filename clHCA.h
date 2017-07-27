#pragma once

//--------------------------------------------------
// HCA(High Compression Audio)�N���X
//--------------------------------------------------
class clHCA {
public:
	clHCA(unsigned int ciphKey1 = 0xE0748978, unsigned int ciphKey2 = 0xCF222F1F);

	// HCA�`�F�b�N
	static bool CheckFile(void *data, unsigned int size);

	// �`�F�b�N�T��
	static unsigned short CheckSum(void *data, int size, unsigned short sum = 0);

	// �w�b�_�����R���\�[���o��
	bool PrintInfo(const char *filenameHCA);

	// ������
	bool Decrypt(const char *filenameHCA);

	// �f�R�[�h����WAVE�t�@�C���ɕۑ�
	bool DecodeToWavefile(const char *filenameHCA, const char *filenameWAV, float volume = 1, int mode = 16, int loop = 0);
	bool DecodeToWavefileStream(void *fpHCA, const char *filenameWAV, float volume = 1, int mode = 16, int loop = 0);

	// �G���R�[�h����HCA�t�@�C���ɕۑ�
	//bool EncodeFromWavefile(const char *filenameWAV,const char *filenameHCA,float volume=1);
	//bool EncodeFromWavefileStream(void *fpWAV,const char *filenameHCA,float volume=1);

private:
	struct stHeader {//�t�@�C����� (�K�{)
		unsigned int hca;              // 'HCA'
		unsigned short version;        // �o�[�W�����Bv1.3��v2.0�̑��݂��m�F
		unsigned short dataOffset;     // �f�[�^�I�t�Z�b�g
	};
	struct stFormat {//�t�H�[�}�b�g��� (�K�{)
		unsigned int fmt;              // 'fmt'
		unsigned int channelCount : 8;   // �`�����l���� 1�`16
		unsigned int samplingRate : 24;  // �T���v�����O���[�g 1�`0x7FFFFF
		unsigned int blockCount;       // �u���b�N�� 0�ȏ�
		unsigned short muteHeader;     // �擪�̖�������(�u���b�N��*0x400+0x80)
		unsigned short muteFooter;     // �����̖����T���v����
	};
	struct stCompress {//���k��� (���k��񂩃f�R�[�h���̂ǂ��炩����K�{)
		unsigned int comp;             // 'comp'
		unsigned short blockSize;      // �u���b�N�T�C�Y(CBR�̂Ƃ��ɗL���H) 8�`0xFFFF�A0�̂Ƃ���VBR
		unsigned char r01;             // �s��(1) 0�`r02      v2.0����1�̂ݑΉ�
		unsigned char r02;             // �s��(15) r01�`0x1F  v2.0����15�̂ݑΉ�
		unsigned char r03;             // �s��(1)(1)
		unsigned char r04;             // �s��(1)(0)
		unsigned char r05;             // �s��(0x80)(0x80)
		unsigned char r06;             // �s��(0x80)(0x20)
		unsigned char r07;             // �s��(0)(0x20)
		unsigned char r08;             // �s��(0)(8)
		unsigned char reserve1;        // �\��
		unsigned char reserve2;        // �\��
	};
	struct stDecode {//�f�R�[�h��� (���k��񂩃f�R�[�h���̂ǂ��炩����K�{)
		unsigned int dec;              // 'dec'
		unsigned short blockSize;      // �u���b�N�T�C�Y(CBR�̂Ƃ��ɗL���H) 8�`0xFFFF�A0�̂Ƃ���VBR
		unsigned char r01;             // �s��(1) 0�`r02      v2.0����1�̂ݑΉ�
		unsigned char r02;             // �s��(15) r01�`0x1F  v2.0����15�̂ݑΉ�
		unsigned char count1;          // type0��type1�̐�-1
		unsigned char count2;          // type2�̐�-1
		unsigned char r03 : 4;           // �s��(0)
		unsigned char r04 : 4;           // �s��(0) 0��1�ɏC�������
		unsigned char enableCount2;    // count2���g���t���O
	};
	struct stVBR {//�σr�b�g���[�g��� (�p�~�H)
		unsigned int vbr;              // 'vbr'
		unsigned short r01;            // �s�� 0�`0x1FF
		unsigned short r02;            // �s��
	};
	struct stATH {//ATH�e�[�u����� (v2.0����p�~�H)
		unsigned int ath;              // 'ath'
		unsigned short type;           // �e�[�u���̎��(0:�S��0 1:�e�[�u��1)
	};
	struct stLoop {//���[�v���
		unsigned int loop;             // 'loop'
		unsigned int start;            // ���[�v�J�n�u���b�N�C���f�b�N�X 0�`loopEnd
		unsigned int end;              // ���[�v�I���u���b�N�C���f�b�N�X loopStart�`(stFormat::blockCount-1)
		unsigned short count;          // ���[�v�� 0x80�Ŗ������[�v
		unsigned short r01;            // �s��(0x226) 
	};
	struct stCipher {//�Í��e�[�u�����
		unsigned int ciph;             // 'ciph'
		unsigned short type;           // �Í����̎��(0:�Í����Ȃ� 1:���Ȃ��Í��� 0x38:������Í���)
	};
	struct stRVA {//���΃{�����[�����ߏ��
		unsigned int rva;              // 'rva'
		float volume;                  // �{�����[��
	};
	struct stComment {//�R�����g���
		unsigned int comm;             // 'comm'
		unsigned char len;             // �R�����g�̒����H
																	 //char comment[];
	};
	struct stPadding {//�p�f�B���O
		unsigned int pad;              // 'pad'
	};
	unsigned int _version;
	unsigned int _dataOffset;
	unsigned int _channelCount;
	unsigned int _samplingRate;
	unsigned int _blockCount;
	unsigned int _muteHeader;
	unsigned int _muteFooter;
	unsigned int _blockSize;
	unsigned int _comp_r01;
	unsigned int _comp_r02;
	unsigned int _comp_r03;
	unsigned int _comp_r04;
	unsigned int _comp_r05;
	unsigned int _comp_r06;
	unsigned int _comp_r07;
	unsigned int _comp_r08;
	unsigned int _comp_r09;
	unsigned int _vbr_r01;
	unsigned int _vbr_r02;
	unsigned int _ath_type;
	unsigned int _loopStart;
	unsigned int _loopEnd;
	unsigned int _loopCount;
	unsigned int _loop_r01;
	bool _loopFlg;
	unsigned int _ciph_type;
	unsigned int _ciph_key1;
	unsigned int _ciph_key2;
	float _rva_volume;
	unsigned int _comm_len;
	char *_comm_comment;
	class clATH {
	public:
		clATH();
		bool Init(int type, unsigned int key);
		unsigned char *GetTable(void);
	private:
		unsigned char _table[0x80];
		void Init0(void);
		void Init1(unsigned int key);
	}_ath;
	class clCipher {
	public:
		clCipher();
		bool Init(int type, unsigned int key1, unsigned int key2);
		void Mask(void *data, int size);
	private:
		unsigned char _table[0x100];
		void Init0(void);
		void Init1(void);
		void Init56(unsigned int key1, unsigned int key2);
		void Init56_CreateTable(unsigned char *table, unsigned char key);
	}_cipher;
	class clData {
	public:
		clData(void *data, int size);
		int CheckBit(int bitSize);
		int GetBit(int bitSize);
		void AddBit(int bitSize);
	private:
		unsigned char *_data;
		int _size;
		int _bit;
	};
	struct stChannel {
		float block[0x80];
		float base[0x80];
		char value[0x80];
		char scale[0x80];
		char value2[8];
		int type;
		char *value3;
		unsigned int count;
		float wav1[0x80];
		float wav2[0x80];
		float wav3[0x80];
		float wave[8][0x80];
		void Decode1(clData *data, unsigned int a, int b, unsigned char *ath);
		void Decode2(clData *data);
		void Decode3(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		void Decode4(int index, unsigned int a, unsigned int b, unsigned int c);
		void Decode5(int index);
	}_channel[0x10];
	bool Decode(void *data, unsigned int size, unsigned int address);
	bool DecodeToWavefile_Decode(void *fp1, void *fp2, unsigned int address, unsigned int count, void *data, void *modeFunction);
	static void DecodeToWavefile_DecodeModeFloat(float f, void *fp);
	static void DecodeToWavefile_DecodeMode8bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode16bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode24bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode32bit(float f, void *fp);
};