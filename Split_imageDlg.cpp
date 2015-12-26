
// Extract_InfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Extract_Info.h"
#include "Split_imageDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#include <opencv2/opencv.hpp>
#include "Preprocess.h"
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExtract_InfoDlg �Ի���



CExtract_InfoDlg::CExtract_InfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExtract_InfoDlg::IDD, pParent)
	, code_info(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_font.CreatePointFont(330, "����");
}

void CExtract_InfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, code_info);
}

BEGIN_MESSAGE_MAP(CExtract_InfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenPic, &CExtract_InfoDlg::OnBnClickedOpenpic)
	ON_BN_CLICKED(IDC_ExtractInfo, &CExtract_InfoDlg::OnBnClickedExtractinfo)
	//	ON_BN_CLICKED(IDC_BUTTON1, &CExtract_InfoDlg::EnCode2)
	//	ON_BN_CLICKED(IDC_BUTTON2, &CExtract_InfoDlg::DeCode)
	ON_WM_CTLCOLOR()
	//	ON_STN_CLICKED(IDC_Title, &CExtract_InfoDlg::OnStnClickedTitle)
	ON_BN_CLICKED(IDC_Decode, &CExtract_InfoDlg::OnBnClickedDecode)
	ON_BN_CLICKED(IDC_OpenCode, &CExtract_InfoDlg::OnBnClickedOpencode)
	ON_BN_CLICKED(IDC_Save, &CExtract_InfoDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CExtract_InfoDlg ��Ϣ�������

BOOL CExtract_InfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ��ͼƬ���Ŵ�С
	Pic_Size = 340;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CExtract_InfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExtract_InfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExtract_InfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
void CProPosalDlg::ShowImage(IplImage* img, unsigned int ID, unsigned int Edit_ID, CString str)
{
if (!img)      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
{
AfxMessageBox(_T("��ȡͼƬʧ��"));
return;
}
CDC* pDC = GetDlgItem(ID)->GetDC();   // �����ʾ�ؼ��� DC
HDC hDC = pDC->GetSafeHdc();			 // ��ȡ HDC(�豸���) �����л�ͼ����

CRect rect;
GetDlgItem(ID)->GetClientRect(&rect);
int ID_size = rect.bottom>rect.right ? rect.right : rect.bottom;//���Picture�ؼ��ĳߴ�
//int b=rect.right;
pDC->FillSolidRect(&rect, RGB(240, 240, 240));//��һ���Ի�����ɫ��䣬��Ȼ����ͼƬ���еط�һֱ����
int iw = img->width;
int ih = img->height;
if (iw >= ih)
ratio = ((float)iw) / ID_size;
else
ratio = ((float)ih) / ID_size;
SetRect(rect, 0, 0, floor((float)iw / ratio), floor((float)ih / ratio));//�ı�rect��С


CvvImage cimg;
cimg.CopyOf(img);
cimg.DrawToHDC(hDC, &rect);	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
if (feaflags == DENSESURF_PRO_VLAD)
{
if (Edit_ID == IDC_EDIT1 || Edit_ID == IDC_EDIT4 || Edit_ID == IDC_EDIT7)
GetDlgItem(Edit_ID)->SetWindowText(str);
else
{
if (Edit_ID >= IDC_EDIT1 && Edit_ID <= IDC_EDIT9)
GetDlgItem(Edit_ID)->SetWindowTextA("              ");
}
}
else
{
if (Edit_ID >= IDC_EDIT1 && Edit_ID <= IDC_EDIT9)
GetDlgItem(Edit_ID)->SetWindowText(str);
}
ReleaseDC(pDC);

}
*/

void CExtract_InfoDlg::ShowImage(IplImage* img, unsigned int ID)
{
	if (!img)      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}
	CDC* pDC = GetDlgItem(ID)->GetDC();   // �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();			 // ��ȡ HDC(�豸���) �����л�ͼ����	

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int ID_size = rect.bottom > rect.right ? rect.right : rect.bottom;//���Picture�ؼ��ĳߴ�
	//int b=rect.right;
	pDC->FillSolidRect(&rect, RGB(240, 240, 240));//��һ���Ի�����ɫ��䣬��Ȼ����ͼƬ���еط�һֱ����
	int iw = img->width;
	int ih = img->height;
	if (iw >= ih)
		ratio = ((float)iw) / ID_size;
	else
		ratio = ((float)ih) / ID_size;
	SetRect(rect, 0, 0, floor((float)iw / ratio), floor((float)ih / ratio));//�ı�rect��С		


	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������

	//��ȡ��Ϣ
	/*
	if (Edit_ID >= IDC_EDIT1 && Edit_ID <= IDC_EDIT9)
	GetDlgItem(Edit_ID)->SetWindowText(str);
	*/
	ReleaseDC(pDC);
}


void CExtract_InfoDlg::OnBnClickedOpenpic()
{
	CFileDialog dlg(
		TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("All Files (*.*) |*.*||"), NULL
		);
	dlg.m_ofn.lpstrTitle = _T("��ѡ��һ����������ͼ��");// ���ļ��Ի���ı�����

	if (dlg.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ
	{
		AfxMessageBox(_T("����˵�����㲻֪��Ҫ��ѡ��ͼƬ��"));
		return;
	}

	mPath = dlg.GetPathName();	    // ��ȡͼƬ·��
	// ·��ת��Ϊ char*
	/*
	const size_t strsize = (mPath.GetLength() + 1) * 2;
	char *mPath_str = new char[strsize];
	size_t sz = 0;
	wcstombs_s(&sz, mPath_str, strsize, mPath, _TRUNCATE);
	*/

	sourceImg = cv::imread((LPCSTR)mPath);
	//sourceImg = cv::imread("K:\\anxingle\\anxingle.jpg");
	//sourceImg = cv::Mat(cvLoadImage((LPCSTR)mPath));

	//sourceImg = cv::imread(mPath_str.GetBuffer());
	//mPath(mPath_str)��Ϊ����·����("E://Programs/Images/Lena.jpg" )  

	if (sourceImg.empty())      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T(mPath));
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}

	cv::Mat Img = cv::Mat(zoomImgByMaxSide(&IplImage(sourceImg), Pic_Size), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size

	ShowImage(&IplImage(Img), IDC_SHOW1);        // ������ʾͼƬ����
}

//��ȡͼƬ�����Ϣ
void CExtract_InfoDlg::OnBnClickedExtractinfo()
{
	// TODO: Add your control notification handler code here
	
	IplImage *pImg = cvLoadImage((LPCSTR)mPath);

	//pImg = cvCreateImage(cvSize(pImg->width, pImg->height), pImg->depth, 4);


	rImg = cvCreateImage(cvSize(pImg->width, pImg->height), pImg->depth, 1);
	bImg = cvCreateImage(cvSize(pImg->width, pImg->height), pImg->depth, 1);
	gImg = cvCreateImage(cvSize(pImg->width, pImg->height), pImg->depth, 1);
	xImg = cvCreateImage(cvSize(pImg->width, pImg->height), pImg->depth, 1);
	cvSplit(pImg, bImg, gImg, rImg, NULL);
	for (int y = 0; y < bImg->height; y++) {
		{
			uchar* ptr = (uchar*)(bImg->imageData + y * bImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < bImg->width; x++)
			{
				if (x / 2 == 0)
					ptr[x] = RSA_decode2(ptr[x]);
				else
					ptr[x] = RSA_decode(ptr[x]);
			}
		}
	}
	for (int y = 0; y < gImg->height; y++) {
		{
			uchar* ptr2 = (uchar*)(gImg->imageData + y * gImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < gImg->width; x++)
			{
				if (x / 2 == 0)
					ptr2[x] = RSA_decode2(ptr2[x]);
				else
					ptr2[x] = RSA_decode(ptr2[x]);
			}
		}
	}
	for (int y = 0; y < rImg->height; y++) {
		{
			uchar* ptr3 = (uchar*)(rImg->imageData + y * rImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < rImg->width; x++)
			{
				if (x / 2 == 0)
					ptr3[x] = RSA_decode2(ptr3[x]);
				else
					ptr3[x] = RSA_decode(ptr3[x]);
			}
		}
	}
	/*
	bImg = EncodeImg(bImg);
	gImg = EncodeImg(gImg);
	rImg = EncodeImg(rImg);
	*/

	cv::Mat Img1 = cv::Mat(zoomImgByMaxSide(rImg, Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	ShowImage(&IplImage(Img1), IDC_SHOW2);
	cv::Mat Img2 = cv::Mat(zoomImgByMaxSide(bImg, Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	ShowImage(&IplImage(Img2), IDC_SHOW3);

	cv::Mat Img3 = cv::Mat(zoomImgByMaxSide(gImg, Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	ShowImage(&IplImage(Img3), IDC_SHOW4);

	cv::Mat Img4 = cv::Mat(zoomImgByMaxSide(xImg, Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	ShowImage(&IplImage(Img4), IDC_SHOW5);


	//	cvMerge(bImg, gImg, rImg, NULL, xImg);
	//cv::Mat Img4 = cv::Mat(zoomImgByMaxSide(xImg, Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	//ShowImage(&IplImage(Img4), IDC_SHOW5);

}

//������Ϣ
//void CExtract_InfoDlg::EnCode2()
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	//char info[40];
//	int fnlen = code_info.GetLength(); //strcspn(str,".");
//	char* codefile = new char[80];
//	codefile = (LPSTR)(LPCTSTR)code_info;//��ȷ����취ȥ����׺
//	
//	//�õ�����֮��Ҫ����ͼƬ
//	uchar code2num[80];
//	for (int loop = 0; loop < 80; loop++)
//	{
//		code2num[loop] = codefile[loop];
//	}
//	IplImage * img = cvLoadImage(mPath, -1);//����ͼ��
//	int count = 0;
//	//for (int y = 0; y<img->height; y++) {
//	for (int y = 1; y < 2; y++)
//	{
//		uchar* ptr = (uchar*)(img->imageData + y * img->widthStep/(sizeof(uchar)));
//		//for (int x = img->width - 12; x < img->width - 1; x++){
//		for (int x = 0; x < 80 ; x++){
//    		ptr[x] = code2num[count++];
//			//for (int x = 0; x<img->width; x++) {
//			//ptr[3 * x + 1] = 255;
//			//ptr[3 * x + 2] = 255;
//		}
//	}
//
//
//	//ShowImage(img, IDC_SHOW1);
//	TCHAR szFilter[] = _T("BMP�ļ�(*.bmp)|*.bmp|PNG�ļ�(*.png)|*.gif|�����ļ�(*.*)|*.*||");
//	// ���챣���ļ��Ի���   
//	CFileDialog fileDlg(FALSE, _T("bmp"), _T("001"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
//	CString strFilePath;
//
//	// ��ʾ�����ļ��Ի���   
//	if (IDOK == fileDlg.DoModal())
//	{
//		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
//		strFilePath = fileDlg.GetPathName();
//		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
//	}
//	cvSaveImage(strFilePath,img);
//	AfxMessageBox("������ɣ� copy right@������");
//	UpdateData(FALSE);
//}



//����
//void CExtract_InfoDlg::DeCode()
//{
//	
//	char* codefile = new char[84];
//	//codefile = (LPSTR)(LPCTSTR)code_info;//��ȷ����취ȥ����׺
//	
//	//AfxMessageBox(codefile);
//	//�õ�����֮��Ҫ����ͼƬ
//	uchar code2num[80];
//	
//	IplImage * img2 = cvLoadImage((LPCSTR)mPath, -1);//����ͼ��
//	int count = 0;
//	for (int loop = 0; loop < 80; loop++)
//	{
//		code2num[loop] ='0';
//		codefile[loop] = '0';
//	}
//	codefile[79] = '\0';
//	//for (int y = 0; y<img->height; y++) {
//	for (int y =1; y< 2; y++) 
//	{
//		uchar* ptr2 = (uchar*)(img2->imageData + y * img2->widthStep/(sizeof(uchar)));
//		for (int x = 0; x < 80; x++)
//		{
//			ptr[3 * x + 1] = code2num[count++];
//			code2num[count++] = ptr2[x];
//		}
//	}
//
//	/*
//	for (int y = 1; y < 2; y++)
//	{
//		uchar* ptr = (uchar*)(img->imageData + y * img->widthStep);
//		//for (int x = img->width - 12; x < img->width - 1; x++){
//		for (int x = 1; x < 11 ; x++){
//    		ptr[x] = code2num[count++];
//			//for (int x = 0; x<img->width; x++) {
//			//ptr[3 * x + 1] = 255;
//			//ptr[3 * x + 2] = 255;
//		}
//	
//	*/
//	for (int loop = 0; loop < 80; loop++)
//	{
//		codefile[loop] = code2num[loop];
//	}
//
//	GetDlgItem(IDC_EDIT3)->SetWindowText(codefile);
//}


HBRUSH CExtract_InfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_Title)
	{
		pDC->SelectObject(&m_font);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


//void CExtract_InfoDlg::OnStnClickedTitle()
//{
//	// TODO: Add your control notification handler code here
//}


unsigned char CExtract_InfoDlg::RSA_decode(unsigned char pixes)
{
	pixes = (int)pixes;
	/*
	switch (pixes)
	{
	case (pixes > 180) :
	pixes -= 200;
	break;
	case(pixes > 110 && pixes <= 180) :
	break;
	case():
	}  */
	if (pixes > 235)
		pixes -= 235;
	else if (pixes > 215 && pixes <= 235)
		pixes -= 195;
	else if (pixes > 195 && pixes <= 215)
		pixes -= 155;
	else if (pixes > 175 && pixes <= 195)
		pixes -= 115;
	else if (pixes > 155 && pixes <= 175)
		pixes -= 75;
	else if (pixes > 135 && pixes <= 155)
		pixes -= 35;
	else if (pixes >= 0 && pixes < 20)
		pixes += 235;
	else if (pixes>=20 &&pixes<40)
		pixes += 195;
	else if (pixes>=40&& pixes<60)
	pixes += 155;
	else if (pixes>=60&& pixes<80)
	pixes += 115;
	else if (pixes>=80&& pixes <100)
	pixes += 75;
	else if (pixes>=100&&pixes <120)
	pixes += 35;
	return pixes;
}
unsigned char CExtract_InfoDlg::RSA_decode2(unsigned char pixes)
{
	if (pixes > 135)
		pixes -= 135;
	else
		pixes += 135;
	return pixes;
}

void CExtract_InfoDlg::EncodeImg(IplImage* src)
{

	for (int y = 0; y < src->height; y++) {
		{
			uchar* ptr = (uchar*)(src->imageData + y * src->widthStep / (sizeof(uchar)));
			for (int x = 0; x < src->width; x++)
			{
				ptr[x] = RSA_decode(ptr[x]);
			}
		}
	}
}


IplImage* CExtract_InfoDlg::DncodeImg(IplImage* src)
{

	for (int y = 0; y < src->height; y++) {
		{
			uchar* ptr = (uchar*)(src->imageData + y * src->widthStep / (sizeof(uchar)));
			for (int x = 0; x < src->width; x++)
			{
				ptr[x] = RSA_decode(ptr[x]);
			}
		}
	}
	return src;
}

//����
void CExtract_InfoDlg::OnBnClickedDecode()
{
	// TODO: Add your control notification handler code here
	IplImage* srcImage = cvCreateImage(cvSize((&IplImage(sourceImg1))->width, (&IplImage(sourceImg1))->height), (&IplImage(sourceImg1))->depth, 3);
	for (int y = 0; y < bImg->height; y++) {
		{
			uchar* ptr = (uchar*)(bImg->imageData + y * bImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < bImg->width; x++)
			{
				if (x / 2 == 0)
					ptr[x] = RSA_decode2(ptr[x]);
				else
					ptr[x] = RSA_decode(ptr[x]);
			}
		}
	}
	for (int y = 0; y < gImg->height; y++) {
		{
			uchar* ptr2 = (uchar*)(gImg->imageData + y * gImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < gImg->width; x++)
			{
				if (x / 2 == 0)
					ptr2[x] = RSA_decode2(ptr2[x]);
				else
					ptr2[x] = RSA_decode(ptr2[x]);
			}
		}
	}
	for (int y = 0; y < rImg->height; y++) {
		{
			uchar* ptr3 = (uchar*)(rImg->imageData + y * rImg->widthStep / (sizeof(uchar)));
			for (int x = 0; x < rImg->width; x++)
			{
				if (x / 2 == 0)
					ptr3[x] = RSA_decode2(ptr3[x]);
				else
					ptr3[x] = RSA_decode(ptr3[x]);
			}
		}
	}
	IplImage *bImg1, *gImg1, *rImg1;
	rImg1 = cvCreateImage(cvSize(srcImage->width, srcImage->height), srcImage->depth, 1);
	bImg1 = cvCreateImage(cvSize(srcImage->width, srcImage->height), srcImage->depth, 1);
	gImg1 = cvCreateImage(cvSize(srcImage->width, srcImage->height), srcImage->depth, 1);
		//&IplImage(sourceImg1);
	cvMerge(bImg, gImg,rImg,NULL,srcImage);

	cv::Mat Img1 = cv::Mat(zoomImgByMaxSide(srcImage, Pic_Size/2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	ShowImage(&IplImage(Img1), IDC_SHOW1);
	//cvReleaseImage(&srcImage);
}


void CExtract_InfoDlg::OnBnClickedOpencode()
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg1(
		TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("All Files (*.*) |*.*||"), NULL
		);
	dlg1.m_ofn.lpstrTitle = _T("��ѡ��һ����������ͼ��");// ���ļ��Ի���ı�����

	if (dlg1.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ
	{
		AfxMessageBox(_T("����˵�����㲻֪��Ҫ��ѡ��ͼƬ��"));
		return;
	}
	mPath1 = dlg1.GetPathName();	    // ��ȡͼƬ·��
	sourceImg1 = cv::imread((LPCSTR)mPath1);
	if (sourceImg1.empty())      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T(mPath));
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}
	cv::Mat Img1 = cv::Mat(zoomImgByMaxSide(&IplImage(sourceImg1), Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	rImg = cvCreateImage(cvSize((&IplImage(sourceImg1))->width, (&IplImage(sourceImg1))->height), (&IplImage(sourceImg1))->depth, 1);
	bImg = cvCreateImage(cvSize((&IplImage(sourceImg1))->width, (&IplImage(sourceImg1))->height), (&IplImage(sourceImg1))->depth, 1);
	gImg = cvCreateImage(cvSize((&IplImage(sourceImg1))->width, (&IplImage(sourceImg1))->height), (&IplImage(sourceImg1))->depth, 1);

	bImg = cvLoadImage((LPCSTR)mPath1,-1);
	ShowImage(&IplImage(Img1), IDC_SHOW2);        // ������ʾͼƬ����
	//**************************************************************************
	CFileDialog dlg2(
		TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("All Files (*.*) |*.*||"), NULL
		);
	dlg2.m_ofn.lpstrTitle = _T("��ѡ��һ����������ͼ��");// ���ļ��Ի���ı�����

	if (dlg2.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ
	{
		AfxMessageBox(_T("����˵�����㲻֪��Ҫ��ѡ��ͼƬ��"));
		return;
	}
	mPath2 = dlg2.GetPathName();	    // ��ȡͼƬ·��
	sourceImg2 = cv::imread((LPCSTR)mPath2,-1);
	if (sourceImg2.empty())      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T(mPath));
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}
	cv::Mat Img2 = cv::Mat(zoomImgByMaxSide(&IplImage(sourceImg2), Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	gImg = cvLoadImage((LPCSTR)mPath2,-1);
	ShowImage(&IplImage(Img2), IDC_SHOW3);        // ������ʾͼƬ����
	//*********************************************************************
	CFileDialog dlg3(
		TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("All Files (*.*) |*.*||"), NULL
		);
	dlg3.m_ofn.lpstrTitle = _T("��ѡ��һ����������ͼ��");// ���ļ��Ի���ı�����

	if (dlg3.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ
	{
		AfxMessageBox(_T("����˵�����㲻֪��Ҫ��ѡ��ͼƬ��"));
		return;
	}
	mPath3 = dlg3.GetPathName();	    // ��ȡͼƬ·��
	sourceImg3 = cv::imread((LPCSTR)mPath3);
	if (sourceImg3.empty())      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T(mPath));
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}

	cv::Mat Img3 = cv::Mat(zoomImgByMaxSide(&IplImage(sourceImg3), Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	rImg = cvLoadImage((LPCSTR)mPath3,-1);
	ShowImage(&IplImage(Img3), IDC_SHOW4);        // ������ʾͼƬ����

	CFileDialog dlg4(
		TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("All Files (*.*) |*.*||"), NULL
		);
	dlg4.m_ofn.lpstrTitle = _T("��ѡ��һ����������ͼ��");// ���ļ��Ի���ı�����

	if (dlg4.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ
	{
		AfxMessageBox(_T("����˵�����㲻֪��Ҫ��ѡ��ͼƬ��"));
		return;
	}

	mPath4 = dlg4.GetPathName();	    // ��ȡͼƬ·��
	sourceImg4 = cv::imread((LPCSTR)mPath4);
	if (sourceImg4.empty())      // �ж��Ƿ�ɹ���ȡͼƬ,��TheImage==NULL�򷵻أ���ִ������Ĳ���
	{
		AfxMessageBox(_T(mPath));
		AfxMessageBox(_T("��ȡͼƬʧ��"));
		return;
	}
	cv::Mat Img4 = cv::Mat(zoomImgByMaxSide(&IplImage(sourceImg4), Pic_Size / 2), false);//��ԭͼ����ѹ����ͼƬ�ؼ��߳�Pic_Size
	xImg = cvLoadImage((LPCSTR)mPath4);
	ShowImage(&IplImage(Img4), IDC_SHOW5);        // ������ʾͼƬ����
}


void CExtract_InfoDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("������ĸ�ͼƬ���б��棡�����������ĸ������ƣ� ");
	TCHAR szFilter1[] = _T("BMP�ļ�(*.bmp)|*.bmp|");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg1(FALSE, _T("bmp"), _T("001"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter1, this);
	CString strFilePath1;
	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg1.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath1 = fileDlg1.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
	cvSaveImage(strFilePath1,bImg);
	TCHAR szFilter2[] = _T("BMP�ļ�(*.bmp)|*.bmp||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg2(FALSE, _T("bmp"), _T("001"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter2, this);
	CString strFilePath2;
	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg2.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath2 = fileDlg2.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
	cvSaveImage(strFilePath2, gImg);
	TCHAR szFilter3[] = _T("BMP�ļ�(*.bmp)|*.bmp|");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg3(FALSE, _T("bmp"), _T("001"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath3;
	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg3.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath3 = fileDlg3.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
	cvSaveImage(strFilePath3, rImg);

	TCHAR szFilter4[] = _T("BMP�ļ�(*.bmp)|*.bmp|");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg4(FALSE, _T("bmp"), _T("001"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath4;
	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg4.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath4 = fileDlg4.GetPathName();
		//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
	}
	cvSaveImage(strFilePath4, xImg);

	AfxMessageBox("������ɣ� copy right@������");


}