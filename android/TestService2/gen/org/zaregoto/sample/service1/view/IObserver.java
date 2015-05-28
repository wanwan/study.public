/*___Generated_by_IDEA___*/

/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: /Users/waka/IdeaProjects/TestService2/src/org/zaregoto/sample/service1/view/IObserver.aidl
 */
package org.zaregoto.sample.service1.view;
public interface IObserver extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements org.zaregoto.sample.service1.view.IObserver
{
private static final java.lang.String DESCRIPTOR = "org.zaregoto.sample.service1.view.IObserver";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an org.zaregoto.sample.service1.view.IObserver interface,
 * generating a proxy if needed.
 */
public static org.zaregoto.sample.service1.view.IObserver asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof org.zaregoto.sample.service1.view.IObserver))) {
return ((org.zaregoto.sample.service1.view.IObserver)iin);
}
return new org.zaregoto.sample.service1.view.IObserver.Stub.Proxy(obj);
}
@Override public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_onDataArrived:
{
data.enforceInterface(DESCRIPTOR);
int _arg0;
_arg0 = data.readInt();
this.onDataArrived(_arg0);
reply.writeNoException();
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements org.zaregoto.sample.service1.view.IObserver
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
@Override public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
@Override public void onDataArrived(int data) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeInt(data);
mRemote.transact(Stub.TRANSACTION_onDataArrived, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
}
static final int TRANSACTION_onDataArrived = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
}
public void onDataArrived(int data) throws android.os.RemoteException;
}
