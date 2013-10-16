/**
 *  @file
 *  @author     This file has been generated by generate-bindings.pl. DO NOT MODIFY!
 *  @copyright  Simplified BSD
 *
 *  @cond
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the FreeBSD license as published by the FreeBSD
 *  project.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the FreeBSD license along with this
 *  program. If not, see <http://www.opensource.org/licenses/bsd-license>.
 *  @endcond
 */


#ifndef V8Uint8ClampedArray_h
#define V8Uint8ClampedArray_h

#include <string>
#include "../../TypedArray.h"
#include "DOM/Node.hpp"
#include "V8ArrayBufferView.h"
#include "string"
#include "uscxml/plugins/datamodel/ecmascript/v8/V8DOM.h"
#include <v8.h>

namespace Arabica {
namespace DOM {

class V8Uint8ClampedArray {
public:
	struct V8Uint8ClampedArrayPrivate {
		V8DOM* dom;
		uscxml::Uint8ClampedArray* nativeObj;
	};

	V8_DESTRUCTOR(V8Uint8ClampedArrayPrivate);
	static bool hasInstance(v8::Handle<v8::Value>);

	static v8::Handle<v8::Value> getCallback(const v8::Arguments&);
	static v8::Handle<v8::Value> setCallback(const v8::Arguments&);
	static v8::Handle<v8::Value> subarrayCallback(const v8::Arguments&);

	static v8::Handle<v8::Value> lengthAttrGetter(v8::Local<v8::String> property, const v8::AccessorInfo& info);
	static v8::Handle<v8::Value> indexedPropertyCustomGetter(uint32_t, const v8::AccessorInfo&);
	static v8::Handle<v8::Value> indexedPropertyCustomSetter(uint32_t, v8::Local<v8::Value>, const v8::AccessorInfo&);

	static v8::Handle<v8::Value> constructor(const v8::Arguments&);
	static v8::Persistent<v8::FunctionTemplate> Constr;
	static v8::Handle<v8::FunctionTemplate> getConstructor() {
		if (Constr.IsEmpty()) {
			v8::Handle<v8::FunctionTemplate> constr = v8::FunctionTemplate::New(constructor);
			Constr = v8::Persistent<v8::FunctionTemplate>::New(constr);
		}
		return Constr;
	}

	static v8::Persistent<v8::FunctionTemplate> Tmpl;
	static v8::Handle<v8::FunctionTemplate> getTmpl() {
		if (Tmpl.IsEmpty()) {
			v8::Handle<v8::FunctionTemplate> tmpl = v8::FunctionTemplate::New();
			tmpl->SetClassName(v8::String::New("Uint8ClampedArray"));
			tmpl->ReadOnlyPrototype();

			v8::Local<v8::ObjectTemplate> instance = tmpl->InstanceTemplate();
			v8::Local<v8::ObjectTemplate> prototype = tmpl->PrototypeTemplate();
			(void)prototype; // surpress unused warnings

			instance->SetInternalFieldCount(1);

			instance->SetAccessor(v8::String::NewSymbol("length"), V8Uint8ClampedArray::lengthAttrGetter, 0,
			                      v8::External::New(0), static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None));

			instance->SetIndexedPropertyHandler(V8Uint8ClampedArray::indexedPropertyCustomGetter, V8Uint8ClampedArray::indexedPropertyCustomSetter);
			prototype->Set(v8::String::NewSymbol("get"),
			               v8::FunctionTemplate::New(V8Uint8ClampedArray::getCallback, v8::Undefined()), static_cast<v8::PropertyAttribute>(v8::DontDelete));
			prototype->Set(v8::String::NewSymbol("set"),
			               v8::FunctionTemplate::New(V8Uint8ClampedArray::setCallback, v8::Undefined()), static_cast<v8::PropertyAttribute>(v8::DontDelete));
			prototype->Set(v8::String::NewSymbol("subarray"),
			               v8::FunctionTemplate::New(V8Uint8ClampedArray::subarrayCallback, v8::Undefined()), static_cast<v8::PropertyAttribute>(v8::DontDelete));

			tmpl->Set(v8::String::NewSymbol("BYTES_PER_ELEMENT"), v8::Integer::New(1), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontEnum));
			prototype->Set(v8::String::NewSymbol("BYTES_PER_ELEMENT"), v8::Integer::New(1), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontEnum));

			tmpl->Inherit(V8ArrayBufferView::getTmpl());
			Tmpl = v8::Persistent<v8::FunctionTemplate>::New(tmpl);
		}
		return Tmpl;
	}


};

}
}

#endif // V8Uint8ClampedArray_h
