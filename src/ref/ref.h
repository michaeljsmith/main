#ifndef __REF_H__
#define __REF_H__

namespace refs
{
	template <typename T> class referenceable
	{
	public:
		typedef T referee_type;

		virtual void add_ref() = 0;
		virtual void release() = 0;
	};

	template <typename T> void intrusive_ptr_add_ref(referenceable<T>* ref)
	{
		static_cast<T*>(ref)->add_ref();
	}

	template <typename T> void intrusive_ptr_release(referenceable<T>* ref)
	{
		static_cast<T*>(ref)->release();
	}

	template <typename T, typename B> class reference_target : public B
	{
	public:
		typedef B base_type;
		typedef T referee_type;

		reference_target();

		virtual void add_ref();
		virtual void release();

	private:
		int ref_count;
	};
}

template <typename T, typename B> inline refs::reference_target<T, B>::reference_target()
: ref_count(0)
{
}

template <typename T, typename B> inline void refs::reference_target<T, B>::add_ref()
{
	++this->ref_count;
}

template <typename T, typename B> inline void refs::reference_target<T, B>::release()
{
	if (--this->ref_count == 0)
		delete static_cast<referee_type*>(this);
}

#endif //__REF_H__
