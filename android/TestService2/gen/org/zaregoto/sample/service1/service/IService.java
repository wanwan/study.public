/*___Generated_by_IDEA___*/

/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: /Users/waka/IdeaProjects/TestService2/src/org/zaregoto/sample/service1/service/IService.aidl
 */
package org.zaregoto.sample.service1.service;
/**
 * Created with IntelliJ IDEA.
 * User: waka
 * Date: 2013/04/09
 * Time: 7:19
 * To change this template use File | Settings | File Templates.
 */
public interface IService extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements org.zaregoto.sample.service1.service.IService
{
private static final java.lang.String DESCRIPTOR = "org.zaregoto.sample.service1.service.IService";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an org.zaregoto.sample.service1.service.IService interface,
 * generating a proxy if needed.
 */
public static org.zaregoto.sample.service1.service.IService asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof org.zaregoto.sample.service1.service.IService))) {
return ((org.zaregoto.sample.service1.service.IService)iin);
}
return new org.zaregoto.sample.service1.service.IService.Stub.Proxy(obj);
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
case TRANSACTION_isForeground:
{
data.enforceInterface(DESCRIPTOR);
boolean _result = this.isForeground();
reply.writeNoException();
reply.writeInt(((_result)?(1):(0)));
return true;
}
case TRANSACTION_setForeground:
{
data.enforceInterface(DESCRIPTOR);
boolean _arg0;
_arg0 = (0!=data.readInt());
this.setForeground(_arg0);
reply.writeNoException();
return true;
}
case TRANSACTION_start:
{
data.enforceInterface(DESCRIPTOR);
this.start();
reply.writeNoException();
return true;
}
case TRANSACTION_stop:
{
data.enforceInterface(DESCRIPTOR);
this.stop();
reply.writeNoException();
return true;
}
case TRANSACTION_clear:
{
data.enforceInterface(DESCRIPTOR);
this.clear();
reply.writeNoException();
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements org.zaregoto.sample.service1.service.IService
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
@Override public boolean isForeground() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
boolean _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_isForeground, _data, _reply, 0);
_reply.readException();
_result = (0!=_reply.readInt());
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public void setForeground(boolean foreground) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeInt(((foreground)?(1):(0)));
mRemote.transact(Stub.TRANSACTION_setForeground, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
@Override public void start() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_start, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
@Override public void stop() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_stop, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
@Override public void clear() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_clear, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
}
static final int TRANSACTION_isForeground = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
static final int TRANSACTION_setForeground = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
static final int TRANSACTION_start = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
static final int TRANSACTION_stop = (android.os.IBinder.FIRST_CALL_TRANSACTION + 3);
static final int TRANSACTION_clear = (android.os.IBinder.FIRST_CALL_TRANSACTION + 4);
}
public boolean isForeground() throws android.os.RemoteException;
public void setForeground(boolean foreground) throws android.os.RemoteException;
public void start() throws android.os.RemoteException;
public void stop() throws android.os.RemoteException;
public void clear() throws android.os.RemoteException;
}
