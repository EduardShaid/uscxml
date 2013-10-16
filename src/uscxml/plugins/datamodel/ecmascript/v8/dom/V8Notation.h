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


#ifndef V8Notation_h
#define V8Notation_h

#include <string>
#include "DOM/Node.hpp"
#include "V8Node.h"
#include "string"
#include "uscxml/plugins/datamodel/ecmascript/v8/V8DOM.h"
#include <v8.h>

namespace Arabica {
namespace DOM {

class V8Notation {
public:
	struct V8NotationPrivate {
		V8DOM* dom;
		Arabica::DOM::Notation<std::string>* nativeObj;
	};

	V8_DESTRUCTOR(V8NotationPrivate);
	static bool hasInstance(v8::Handle<v8::Value>);


	static v8::Handle<v8::Value> publicIdAttrGetter(v8::Local<v8::String> property, const v8::AccessorInfo& info);
	static v8::Handle<v8::Value> systemIdAttrGetter(v8::Local<v8::String> property, const v8::AccessorInfo& info);

	static v8::Persistent<v8::FunctionTemplate> Tmpl;
	static v8::Handle<v8::FunctionTemplate> getTmpl() {
		if (Tmpl.IsEmpty()) {
			v8::Handle<v8::FunctionTemplate> tmpl = v8::FunctionTemplate::New();
			tmpl->SetClassName(v8::String::New("Notation"));
			tmpl->ReadOnlyPrototype();

			v8::Local<v8::ObjectTemplate> instance = tmpl->InstanceTemplate();
			v8::Local<v8::ObjectTemplate> prototype = tmpl->PrototypeTemplate();
			(void)prototype; // surpress unused warnings

			instance->SetInternalFieldCount(1);

			instance->SetAccessor(v8::String::NewSymbol("publicId"), V8Notation::publicIdAttrGetter, 0,
			                      v8::External::New(0), static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None));
			instance->SetAccessor(v8::String::NewSymbol("systemId"), V8Notation::systemIdAttrGetter, 0,
			                      v8::External::New(0), static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None));



			tmpl->Inherit(V8Node::getTmpl());
			Tmpl = v8::Persistent<v8::FunctionTemplate>::New(tmpl);
		}
		return Tmpl;
	}


};

}
}

#endif // V8Notation_h
