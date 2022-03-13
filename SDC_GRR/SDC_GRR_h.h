

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Mar 13 22:25:38 2022
 */
/* Compiler settings for SDC_GRR.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SDC_GRR_h_h__
#define __SDC_GRR_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISDC_GRR_FWD_DEFINED__
#define __ISDC_GRR_FWD_DEFINED__
typedef interface ISDC_GRR ISDC_GRR;

#endif 	/* __ISDC_GRR_FWD_DEFINED__ */


#ifndef __SDC_GRR_FWD_DEFINED__
#define __SDC_GRR_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDC_GRR SDC_GRR;
#else
typedef struct SDC_GRR SDC_GRR;
#endif /* __cplusplus */

#endif 	/* __SDC_GRR_FWD_DEFINED__ */


#ifndef __IPropertySetting_FWD_DEFINED__
#define __IPropertySetting_FWD_DEFINED__
typedef interface IPropertySetting IPropertySetting;

#endif 	/* __IPropertySetting_FWD_DEFINED__ */


#ifndef __PropertySetting_FWD_DEFINED__
#define __PropertySetting_FWD_DEFINED__

#ifdef __cplusplus
typedef class PropertySetting PropertySetting;
#else
typedef struct PropertySetting PropertySetting;
#endif /* __cplusplus */

#endif 	/* __PropertySetting_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SDC_GRR_LIBRARY_DEFINED__
#define __SDC_GRR_LIBRARY_DEFINED__

/* library SDC_GRR */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SDC_GRR;

#ifndef __ISDC_GRR_DISPINTERFACE_DEFINED__
#define __ISDC_GRR_DISPINTERFACE_DEFINED__

/* dispinterface ISDC_GRR */
/* [uuid] */ 


EXTERN_C const IID DIID_ISDC_GRR;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("544909A9-A5EE-4EE2-B44F-AE4B18AB469B")
    ISDC_GRR : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ISDC_GRRVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISDC_GRR * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISDC_GRR * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISDC_GRR * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISDC_GRR * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISDC_GRR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISDC_GRR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISDC_GRR * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ISDC_GRRVtbl;

    interface ISDC_GRR
    {
        CONST_VTBL struct ISDC_GRRVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDC_GRR_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISDC_GRR_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISDC_GRR_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISDC_GRR_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISDC_GRR_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISDC_GRR_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISDC_GRR_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ISDC_GRR_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SDC_GRR;

#ifdef __cplusplus

class DECLSPEC_UUID("2C049595-793A-4542-98B9-CE4247B304AF")
SDC_GRR;
#endif

#ifndef __IPropertySetting_DISPINTERFACE_DEFINED__
#define __IPropertySetting_DISPINTERFACE_DEFINED__

/* dispinterface IPropertySetting */
/* [uuid] */ 


EXTERN_C const IID DIID_IPropertySetting;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("23EE47A6-B3C3-4FC2-997A-020343919E4F")
    IPropertySetting : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IPropertySettingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropertySetting * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropertySetting * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropertySetting * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropertySetting * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropertySetting * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropertySetting * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropertySetting * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IPropertySettingVtbl;

    interface IPropertySetting
    {
        CONST_VTBL struct IPropertySettingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertySetting_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropertySetting_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropertySetting_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropertySetting_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPropertySetting_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPropertySetting_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPropertySetting_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IPropertySetting_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PropertySetting;

#ifdef __cplusplus

class DECLSPEC_UUID("3B4B91B1-490B-4928-A64C-A658DBD4362A")
PropertySetting;
#endif
#endif /* __SDC_GRR_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


