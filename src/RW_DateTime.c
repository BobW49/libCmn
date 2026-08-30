// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      Specific Date and Time (RW_DateTime) Object Support
//****************************************************************


/*
 * File:   RW_DateTime.c
 *  Generated 05/31/2026 10:01:12
 *
 */

 
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <RW_DateTime_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //****************************************************************
    //            Convert from Gregorian Date to Julian
    //****************************************************************

    ERESULT         RW_DateTime_FromGregorian(
        int16_t         iYear,
        int16_t         iMonth,
        int16_t         iDay,
        int16_t         *piJulianDay
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        long            T1;
        int32_t         Work = 0;

        // Do initialization.
        if( piJulianDay )
            *piJulianDay = 0;
        if( (iDay < 1) || (iDay > 31) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (iMonth < 1) || (iMonth > 12) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }

        // Do the conversion.
        T1 = (iMonth - 14L) / 12L;
        Work = (int32_t)((iDay - 32075L)
                + ((1461L * (iYear + 4800 + T1)) / 4L)
                + (367L * (iMonth - 2L - T1 * 12L) / 12L)
                - (3L * ((iYear + 4900L + T1) / 100L) / 4L));

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( piJulianDay )
            *piJulianDay = Work;
        return eRc;
    }




    //****************************************************************
    //            Convert from HH:MM:SS to Milliseconds
    //****************************************************************

    ERESULT         RW_DateTime_FromHHMMSS (
        int16_t         Hour,
        int16_t         Minute,
        int16_t         Second,
        int16_t         Milli,
        int32_t         *pMilSec
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         Work = 0;

        // Do initialization.
        if( (Hour < 0) || (Hour > 24) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Minute < 0) || (Minute > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Second < 0) || (Second > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Milli < 0) || (Milli > 999) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }

        // Do the conversion.
        Work += 60 * Hour;
        Work += Minute;
        Work *= 60;
        Work += Second;
        Work *= 1000;
        Work += Milli;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( pMilSec )
            *pMilSec = Work;
        return eRc;
    }




    //****************************************************************
    //            Convert from Julian Date to Gregorian
    //****************************************************************

    ERESULT         RW_DateTime_ToGregorian (
        int32_t         JulNum,
        int16_t         *pDay,
        int16_t         *pMonth,
        int16_t         *pYear
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        long            t1;
        long            t2;
        long            mo;
        long            yr;
        long            wrk;

        // Do initialization.

        // Do the conversion.
#ifdef  XXX
        t1 = JulDay + 68569L;
        t2 = (4L * t1) / 146097L;
        t1 = t1 - (((146097L * t2) + 3L) / 4L);
        yr = (4000L * (t1 + 1L)) / 1461001L;
        t1 = t1 - ((1461L * yr) / 4L) + 31L;
        mo = (80L * t1) / 2447L;
        *pDay = (int16_t)(t1 - ((2447L * mo) / 80L));
        t1 = mo / 11L;
        *pMonth = (int16_t)(mo + 2L - (12L * t1));
        *pYear = (int16_t)((100L * (t2 - 49L)) + yr + t1);
#else
        t1 = JulNum + 68569L;
        t2 = 4L * t1 / 146097L;
        t1 = t1 - (146097L * t2 + 3L) / 4L;
        yr = 4000L * (t1 + 1L) / 1461001L;
        t1 = t1 - 1461L * yr / 4L + 31L;
        mo = 80L * t1 / 2447L;
        if( pDay ) {
            wrk  = t1 - ((2447L * mo) / 80L);
            *pDay = (int16_t)wrk;
        }
        t1 = mo / 11L;
        if( pMonth ) {
            wrk    = mo + 2L - 12L * t1;
            *pMonth = (int16_t)wrk;
        }
        if( pYear ) {
            wrk   = 100L * (t2 - 49L) + yr + t1;
            *pYear = (int16_t)wrk;
        }
#endif

        // Return to caller.
        return eRc;
    }




    //****************************************************************
    //            Convert from Milliseconds to HH:MM:SS
    //****************************************************************

    ERESULT         RW_DateTime_ToHHMMSS (
        int32_t         milSec,
        int16_t         *Hour,
        int16_t         *Minute,
        int16_t         *Second,
        int16_t         *Milli
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         Work = milSec;

        // Do initialization.

        // Do the conversion.
        if( Milli )
            *Milli = (int16_t)(Work % 1000);
        Work /= 1000;
        if( Second )
            *Second = (int16_t)(Work % 60);
        Work /= 60;
        if( Minute )
            *Minute = (int16_t)(Work % 60);
        Work /= 60;
        if( Hour )
            *Hour = (int16_t)(Work % 24);

        // Return to caller.
        return( eRc );
    }



    //****************************************************************
    //                  Convert to/from uint64
    //****************************************************************

    ERESULT         RW_DateTime_FromUInt64 (
        uint64_t        time,
        int16_t         *pYear,
        int16_t         *pMonth,
        int16_t         *pDay,
        int16_t         *pHours,
        int16_t         *pMins,
        int16_t         *pSecs,
        int16_t         *pMilli
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        work1 = 0;
        uint32_t        work2 = 0;

        // Do initialization.
        work1 = (uint32_t)(time / 1000000000ULL);
        work2 = (uint32_t)(time % 1000000000ULL);

        // Do the conversion.
        if( pDay ) {
            *pDay = (int16_t)(work1 % 100);
        }
        work1 /= 100;
        if( pMonth ) {
            *pMonth = (int16_t)(work1 % 100);
        }
        work1 /= 100;
        if( pYear ) {
            *pYear = (int16_t)(work1);
        }
        if( pMilli ) {
            *pMilli = (int16_t)(work2 % 1000);
        }
        work2 /= 1000;
        if( pSecs ) {
            *pSecs = (int16_t)(work2 % 60);
        }
        work2 /= 60;
        if( pMins ) {
            *pMins = (int16_t)(work2 % 60);
        }
        work2 /= 60;
        if( pHours ) {
            *pHours = (int16_t)(work2 % 24);
        }

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    //Exit00:
        return eRc;
    }



    ERESULT         RW_DateTime_ToUInt64 (
        int16_t         year,
        int16_t         month,
        int16_t         day,
        int16_t         hours,
        int16_t         mins,
        int16_t         secs,
        int16_t         milli,
        uint64_t        *pTime
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        work1 = 0;
        uint32_t        work2 = 0;
        uint64_t        work = 0;

        // Do initialization.
        if( (month < 1) || (month > 12) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (day < 1) || (day > 31) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (hours < 0) || (hours > 24) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (mins < 0) || (mins > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (secs < 0) || (secs > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (milli < 0) || (milli > 999) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }

        // Do the conversion.
        work1 += year;
        work1 *= 100;
        work1 += month;
        work1 *= 100;
        work1 += day;
        work2 += 60 * hours;
        work2 += mins;
        work2 *= 60;
        work2 += secs;
        work2 *= 1000;
        work2 += milli;

        // Return to caller.
        work = (work1 * 1000000000ULL) + work2;
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( pTime )
            *pTime = work;
        return eRc;
    }






    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    RW_DATETIME_DATA * 
                    RW_DateTime_Alloc (
        void
    )
    {
        RW_DATETIME_DATA 
                        *this;
        uint32_t        cbSize = sizeof(RW_DATETIME_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    RW_DATETIME_DATA * 
                    RW_DateTime_New (
        void
    )
    {
        RW_DATETIME_DATA 
                        *this;
        
        this = RW_DateTime_Alloc( );
        if (this) {
            this = RW_DateTime_Init(this);
        } 
        return this;
    }



    RW_DATETIME_DATA *     
                    RW_DateTime_NewCurrent (
        void
    )
    {
        RW_DATETIME_DATA
                        *this;
        time_t          current;
        struct tm       current_time;
        ERESULT         eRc;

        this = RW_DateTime_Alloc( );
        if (this) {
            this = RW_DateTime_Init(this);
            if (this) {
                current = time(NULL);
                if (gmtime_r(&current, &current_time) == NULL) {
                    //perror("gmtime_r");
                    obj_Release(this);
                    return OBJ_NIL;
                }                
                current_time.tm_year += 1900;
                ++current_time.tm_mon;
                eRc =   RW_DateTime_ToUInt64(
                                    current_time.tm_year,
                                    current_time.tm_mon,
                                    current_time.tm_mday,
                                    current_time.tm_hour,
                                    current_time.tm_min,
                                    current_time.tm_sec,
                                    0,
                                    &this->time
                        );
            }
        }
        return this;
    }



    RW_DATETIME_DATA *     
                    RW_DateTime_NewFromTimeT (
        const
        time_t          time
    )
    {
        RW_DATETIME_DATA   
                        *this;
        struct tm       *pTime;
        ERESULT         eRc;
        struct tm       tmWork;

        this = RW_DateTime_Alloc( );
        if (this) {
            this = RW_DateTime_Init(this);
            if (this) {
                pTime = gmtime_r(&time, &tmWork);
                pTime->tm_year += 1900;
                ++pTime->tm_mon;
                eRc =   RW_DateTime_ToUInt64(
                                          pTime->tm_year,
                                          pTime->tm_mon,
                                          pTime->tm_mday,
                                          pTime->tm_hour,
                                          pTime->tm_min,
                                          pTime->tm_sec,
                                          0,
                                          &this->time
                        );
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          D a y
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getDay (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, NULL, &value, NULL, NULL, NULL, NULL);

        return value;
    }


    bool            RW_DateTime_setDay (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        day = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          F l a g
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    // @property Flag
    //  assumes a 1-byte flag in this object.

    bool            RW_DateTime_getFlag (
        RW_DATETIME_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->flag ? true : false;
    }


    bool            RW_DateTime_setFlag (
        RW_DATETIME_DATA 
                        *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = fValue ? 1 : 0;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                      H o u r
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getHour (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, NULL, NULL, &value, NULL, NULL, NULL);

        return value;
    }


    bool            RW_DateTime_setHour (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        hour = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   RW_DATETIME_MSGS
    bool            RW_DateTime_setMsgs (
        RW_DATETIME_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMsgInfo = pMsgInfo;
        this->pMsgWarn = pMsgWarn;
        this->pMsgObj = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          M i l l i
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getMilli (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, NULL, &value);

        return value;
    }


    bool            RW_DateTime_setMilli (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        milli = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          M i n
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getMin (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, &value, NULL, NULL);

        return value;
    }


    bool            RW_DateTime_setMin (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        minute = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          M o n t h
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getMonth (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, &value, NULL, NULL, NULL, NULL, NULL);

        return value;
    }


    bool            RW_DateTime_setMonth (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        month = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    uint16_t        RW_DateTime_getPriority (
        RW_DATETIME_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            RW_DateTime_setPriority (
        RW_DATETIME_DATA 
                        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          S e c
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getSec (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, &value, NULL);

        return value;
    }


    bool            RW_DateTime_setSec (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        second = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        RW_DateTime_getSize (
        RW_DATETIME_DATA 
                        *this
    )
    {
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  RW_DATETIME_SUPER_DEFINED
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  RW_DateTime_getSuperVtbl (
        RW_DATETIME_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T i m e
    //---------------------------------------------------------------
    
    uint64_t        RW_DateTime_getTime (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->time;
    }


    bool            RW_DateTime_setTime (
        RW_DATETIME_DATA 
                        *this,
        uint64_t        value
    )
    {

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->time = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          Y e a r
    //---------------------------------------------------------------
    
    int16_t         RW_DateTime_getYear (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = RW_DateTime_FromUInt64(this->time, &value, NULL, NULL, NULL, NULL, NULL, NULL);

        return value;
    }


    bool            RW_DateTime_setYear (
        RW_DATETIME_DATA 
                        *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hour;
        int16_t         minute;
        int16_t         second;
        int16_t         milli;

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        year = value;
        eRc =   RW_DateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );
        if (ERESULT_FAILED(eRc)) {
            return false;
        }

        return true;
    }



    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = RW_DateTime_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another RW_DATETIME object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         RW_DateTime_Assign (
        RW_DATETIME_DATA 
                        *this,
        RW_DATETIME_DATA 
                        *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!RW_DateTime_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pStr) {
            obj_Release(pOther->pStr);
            pOther->pStr = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pStr) {
            if (obj_getVtbl(this->pStr)->pCopy) {
                pOther->pStr = obj_getVtbl(this->pStr)->pCopy(this->pStr);
            }
            else {
                obj_Retain(this->pStr);
                pOther->pStr = this->pStr;
            }
        }
#endif

        // Copy other data from this object to other.
        pOther->time = this->time;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             RW_DateTime_Compare (
        RW_DATETIME_DATA 
                        *this,
        RW_DATETIME_DATA 
                        *pOther
    )
    {
        int             iRc = -1;
        int64_t         work;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_DATETIME_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_DateTime_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!RW_DateTime_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        work = this->time - pOther->time;
        if (0 == work) {
            iRc = 0;
        } else if (work < 0) {
            iRc = -1;
        } else {
            iRc = 1;
        }
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        RW_DateTime      *pCopy = RW_DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_Copy (
        RW_DATETIME_DATA 
                        *this
    )
    {
        RW_DATETIME_DATA 
                        *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef RW_DATETIME_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = RW_DateTime_New( );
        if (pOther) {
            eRc = RW_DateTime_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            RW_DateTime_Dealloc (
        OBJ_ID          objId
    )
    {
        RW_DATETIME_DATA 
                        *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((RW_DATETIME_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //RW_DateTime_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        RW_DateTime      *pDeepCopy = RW_DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_DeepCopy (
        RW_DATETIME_DATA 
                        *this
    )
    {
        RW_DATETIME_DATA 
                        *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = RW_DateTime_New( );
        if (pOther) {
            eRc = RW_DateTime_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         RW_DateTime_Disable (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_DATETIME_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_DateTime_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         RW_DateTime_Enable (
        RW_DATETIME_DATA 
                        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_DATETIME_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_DateTime_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   RW_DATETIME_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        RW_DateTime_Hash(
        RW_DATETIME_DATA 
                        *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !RW_DateTime_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
       
        hash = (uint32_t)(this->time >> 32) | (uint32_t)(this->time & 0xFFFFFFFF);
        
        return hash;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    RW_DATETIME_DATA * 
                    RW_DateTime_Init (
        RW_DATETIME_DATA 
                        *this
    )
    {
        uint32_t        cbSize = sizeof(RW_DATETIME_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef  RW_DATETIME_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_RW_DATETIME);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&RW_DateTime_Vtbl);
#ifdef  RW_DATETIME_JSON_SUPPORT
        JsonIn_RegisterClass(RW_DateTime_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "RW_DateTime::sizeof(RW_DATETIME_DATA) = %lu\n", 
                sizeof(RW_DATETIME_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(RW_DATETIME_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            RW_DateTime_IsEnabled (
        RW_DATETIME_DATA 
                        *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_DATETIME_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_DateTime_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = RW_DateTime_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "RW_DateTime", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          RW_DateTime_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RW_DATETIME_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RW_DATETIME_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)RW_DateTime_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'T':
                        if (str_Compare("Time", (char *)pStrA) == 0) {
                            return (void *)this->time;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStrA) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStrA) == 0) {
                            return RW_DateTime_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return RW_DateTime_Enable;
                        }
                        break;

                    case 'P':
#ifdef  RW_DATETIME_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return RW_DateTime_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return RW_DateTime_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return RW_DateTime_ToDebugString;
                        }
#ifdef  RW_DATETIME_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return RW_DateTime_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return RW_DateTime_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == RW_DateTime_ToDebugString)
                    return "ToDebugString";
#ifdef  RW_DATETIME_JSON_SUPPORT
                if (pData == RW_DateTime_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RW_DateTime_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToDebugString (
        RW_DATETIME_DATA 
                        *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t         milli;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    RW_DateTime_getSize(this),
                    obj_getRetainCount(this)
            );

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\t%04d/%2d/%2d %3d:%02d:%02d.%03d\n",
                    year,
                    month,
                    day,
                    hours,
                    mins,
                    secs,
                    milli
            );
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     RW_DateTime_ToFileString(
        RW_DATETIME_DATA      
                        *this
    )
    {
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t         milli;

#ifdef NDEBUG
#else
        if( !RW_DateTime_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                                    );
        pStr = AStr_New();
        AStr_AppendPrint(
                         pStr,
                         "%04d.%02d.%02d_%02d.%02d.%02d.%03d",
                         year,
                         month,
                         day,
                         hours,
                         mins,
                         secs,
                         milli
                         );

        return pStr;
    }



    ASTR_DATA *     RW_DateTime_ToString(
        RW_DATETIME_DATA      
                        *this
    )
    {
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t         milli;

#ifdef NDEBUG
#else
        if( !RW_DateTime_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        eRc =   RW_DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                                    );
        pStr = AStr_New();
        AStr_AppendPrint(
                     pStr,
                     "%2d/%2d/%04d %2d:%02d:%02d.%03d",
                     month,
                     day,
                     year,
                     hours,
                     mins,
                     secs,
                     milli
        );

        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            RW_DateTime_Validate (
        RW_DATETIME_DATA 
                        *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_RW_DATETIME))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(RW_DATETIME_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


