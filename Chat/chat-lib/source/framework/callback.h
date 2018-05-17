#ifndef CALLBACK_H
#define CALLBACK_H

//Each function/method needs to know what object it is part of

// t = return type
// o = object definition
// c = callback
#define  CALLBACK(t, o, c) (t (o::*)() )(&o::c)


namespace chat {
namespace framework {

//T - return type
template <class T>
class ICallbackPtrBase
{
public:

    virtual T callback() = 0;
    virtual T callback(void* arg1) = 0;
    virtual T callback(void* arg1, void* arg2) = 0;

};

//O - object definition
//T - return type
template<class O, class T>
class CallbackPtr : public ICallbackPtrBase<T>
{
    typedef T (O::*PCALLBACK)();
    typedef T (O::*PCALLBACK1)(void*);
    typedef T (O::*PCALLBACK2)(void*, void*);

public:
    CallbackPtr(O* _Object, PCALLBACK _Callback) : Object (_Object), pCallback( _Callback) {}

private:
    O* Object;
    PCALLBACK pCallback;

public:
    void SetObject(O* _Object) { Object = _Object;}
    void SetMethod(PCALLBACK _pCallback) { pCallback = _pCallback; }

    //0 args
    virtual T callback()
    {
        return (Object->*pCallback)();
    }

    //1 arg
    virtual T callback(void* arg1)
    {
        return (Object->*(PCALLBACK1)pCallback)(arg1);
    }

    //2 args
    virtual T callback(void* arg1, void* arg2)
    {
        return (Object->*(PCALLBACK2)pCallback)(arg1, arg2);
    }
};



}
}
#endif // CALLBACK_H
