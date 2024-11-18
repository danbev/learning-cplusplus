#include <stdio.h>
#include <string>
#include <map>
#include <climits>
#include <vector>
#include <cstdarg>

// This specified that the first argument is the format string and the 
// rest are the arguments to be formatted.
__attribute__((format(printf, 1, 2)))
static std::string format(const char * fmt, ...) {
    va_list ap;
    va_list ap2;
    va_start(ap, fmt);
    va_copy(ap2, ap);
    int size = vsnprintf(NULL, 0, fmt, ap);
    std::vector<char> buf(size + 1);
    int size2 = vsnprintf(buf.data(), size + 1, fmt, ap2);
    va_end(ap2);
    va_end(ap);
    return std::string(buf.data(), size);
}

// Language Model enums and structs
enum llm_arch {
    LLM_ARCH_LLAMA,
    LLM_ARCH_UNKNOWN,
};

enum llm_tensor {
    LLM_TENSOR_TOKEN_EMBD,
    LLM_TENSOR_ATTN_NORM,
};

static const std::map<llm_arch, std::map<llm_tensor, std::string>> LLM_TENSOR_NAMES = {
    {
        LLM_ARCH_LLAMA,
        {
            { LLM_TENSOR_TOKEN_EMBD, "token_embd" },
            { LLM_TENSOR_ATTN_NORM,  "blk.%d.attn_norm" },
        }
    }
};

// Vision Model enums and structs:
enum vision_tensor {
    VISION_TENSOR_MMPROJ_A,
};

enum vision_arch {
    VISION_ARCH_LLAVA,
    VISION_ARCH_UNKNOWN,
};

static const std::map<vision_arch, std::map<vision_tensor, std::string>> VISION_TENSOR_NAMES = {
    {
        VISION_ARCH_LLAVA,
        {
            { VISION_TENSOR_MMPROJ_A, "v.mmproj_a" },
        }
    }
};


// Tensor Name Implementation
template<typename arch_type, typename tensor_type>
struct TN_IMPL {
    const arch_type arch;
    const tensor_type tensor;
    const char * const suffix;
    const int bid;
    const int xid;
    const std::map<arch_type, std::map<tensor_type, std::string>>& name_mapping;

    TN_IMPL(arch_type a,
                tensor_type t,
                const char* s,
                int b,
                int x,
                const std::map<arch_type, std::map<tensor_type, std::string>>& nm) :
        arch(a), tensor(t), suffix(s), bid(b), xid(x), name_mapping(nm) {}

    std::string str() const {
        if (name_mapping.at(arch).find(tensor) == name_mapping.at(arch).end()) {
            return "__missing__";
        }

        std::string name = ::format(name_mapping.at(arch).at(tensor).c_str(), bid, xid);

        if (suffix != nullptr) {
            name += ".";
            name += suffix;
        }

        return name;
    }

    operator std::string() const {
        return str();
    }

    friend bool operator==(const std::string & str, const TN_IMPL & tn) {
        return str == tn.str();
    }

    friend bool operator!=(const std::string & str, const TN_IMPL & tn) {
        return str != tn.str();
    }
};

struct LLM_TN {
    llm_arch arch;
    const std::map<llm_arch, std::map<llm_tensor, std::string>>& name_mapping;

    LLM_TN(llm_arch arch, const std::map<llm_arch, std::map<llm_tensor, std::string>>& name_mapping) :
        arch(arch), name_mapping(name_mapping) {}

    TN_IMPL<llm_arch, llm_tensor> operator()(llm_tensor tensor, const char * suffix, int bid = -1, int xid = -1) const {
        return TN_IMPL<llm_arch, llm_tensor>(arch, tensor, suffix, bid, xid, name_mapping);
    }

    TN_IMPL<llm_arch, llm_tensor> operator()(llm_tensor tensor, int bid = -1, int xid = -1) const {
        return TN_IMPL<llm_arch, llm_tensor>(arch, tensor, nullptr, bid, xid, name_mapping);
    }
};

struct VL_TN {
    vision_arch arch;
    const std::map<vision_arch, std::map<vision_tensor, std::string>>& name_mapping;

    VL_TN(vision_arch arch, const std::map<vision_arch, std::map<vision_tensor, std::string>>& name_mapping) :
        arch(arch), name_mapping(name_mapping) {}

    TN_IMPL<vision_arch, vision_tensor> operator()(vision_tensor tensor, const char * suffix, int bid = -1, int xid = -1) const {
        return TN_IMPL<vision_arch, vision_tensor>(arch, tensor, suffix, bid, xid, name_mapping);
    }

    TN_IMPL<vision_arch, vision_tensor> operator()(vision_tensor tensor, int bid = -1, int xid = -1) const {
        return TN_IMPL<vision_arch, vision_tensor>(arch, tensor, nullptr, bid, xid, name_mapping);
    }
};

// So I want to be able to print both the TN_IMPL and the VISION_TN_IMPL
template<typename arch_type, typename tensor_type>
void print_tensor_name(const TN_IMPL<arch_type, tensor_type> & tn) {
    printf("%s\n", tn.str().c_str());
}

int main([[maybe_unused]]int argc,[[maybe_unused]] char *argv[]) {
    const LLM_TN tn = LLM_TN(LLM_ARCH_LLAMA, LLM_TENSOR_NAMES);

    TN_IMPL<llm_arch, llm_tensor> embd = tn(LLM_TENSOR_TOKEN_EMBD, "weight", 0, 0);
    print_tensor_name(embd);

    TN_IMPL<llm_arch, llm_tensor> norm = tn(LLM_TENSOR_ATTN_NORM, "weight", 3, 0);
    print_tensor_name(norm);

    VL_TN vtn = VL_TN(VISION_ARCH_LLAVA, VISION_TENSOR_NAMES);
    TN_IMPL<vision_arch, vision_tensor> mmproj_a = vtn(VISION_TENSOR_MMPROJ_A, "weight", 0, 0);
    print_tensor_name(mmproj_a);

    auto create_tensor = []<typename arch_type, typename tensor_type>(
        const TN_IMPL<arch_type, tensor_type>& tn,
        const std::initializer_list<int64_t>& ne,
        int flags
    ) {
        print_tensor_name(tn);
        tensor_type tt = tn.tensor;
    };
    create_tensor(embd, {1, 2, 3}, 0);
    create_tensor(mmproj_a, {1, 2, 3}, 0);

    return 0;
}
