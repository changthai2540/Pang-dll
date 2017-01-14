#include "Global.h"


CCompressionPacket::CCompressionPacket()
{
	m_Buffer = new BYTE[1024*35];
	Init();
}

void CCompressionPacket::Init()
{
	
	//__lzo_init_v2(MINILZO_VERSION, 2, 4, 4, 4, 4, 4, 4, 4, 24);
	m_bLzoUsed = false;
}

int CCompressionPacket::Compress(const unsigned char* pSrc, int srcSize)
{
	if (lzo_init() != LZO_E_OK)
	{
		printf("internal error - lzo_init() failed !!!\n");
		return 1;
	}

	int r;
	lzo_uint in_len = srcSize;

	if (!m_bLzoUsed)
	{
		m_bLzoUsed = true;

				
		lzo_uint DestSize;
		BYTE wrkmem[LZO1X_1_MEM_COMPRESS];

		memset(m_Buffer, 0, 30 * 1024);
		m_Buffer[3] = srcSize + srcSize / 255;
		m_Buffer[2] = ((srcSize - m_Buffer[3]) / 255) + ((srcSize - m_Buffer[3]) / 255) / 255;
		m_Buffer[1] = ((((srcSize - m_Buffer[3]) / 255) - m_Buffer[2]) / 255) + ((((srcSize - m_Buffer[3]) / 255) - m_Buffer[2]) / 255) / 255;

	
		r = lzo1x_1_compress((const unsigned char *)pSrc, in_len, &m_Buffer[4], &DestSize, wrkmem);
		if (r != LZO_E_OK)
		{
			printf("Failed to compress the buffer - Error %i\n", r);
			return 1;
		}

		m_iSize = (DWORD)DestSize + 4;
		return 0;
	}
	else
	{
		printf("Buffer lzo allready used !\n");
		return 1;
	}
}

int CCompressionPacket::Decompress(const unsigned char* pSrc, int srcSize) 
{
	if (lzo_init() != LZO_E_OK)
	{
		printf("internal error - lzo_init() failed !!!\n");
		return 0;
	}

	if (!m_bLzoUsed)
	{
		m_bLzoUsed = true;
		int r;
		lzo_uint in_len = srcSize;
		lzo_uint new_len;
		BYTE wrkmem[LZO1X_1_MEM_COMPRESS];

		memset(m_Buffer, 0, 30 * 1024);
		r = lzo1x_decompress(pSrc, in_len, m_Buffer, &new_len, wrkmem);

		m_iSize = new_len;

		if (r != LZO_E_OK)
		{
			printf("Failed to decompress the buffer - Error %i\n", r);
			return 0;
		}

		return (unsigned long)new_len;
	}
	else
	{
		printf("Buffer lzo allready used !\n");
		return 0;
	}
}

unsigned char* CCompressionPacket::GetNewBuffer()
{
	if (m_iSize)
	{
		m_bLzoUsed = false;
		return m_Buffer;
	}
	else
		return NULL;
}

int CCompressionPacket::Max(int a, int b)
{
	if (a <= b)
		return b;
	return a;
}