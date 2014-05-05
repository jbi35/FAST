#ifndef GAUSSIANSMOOTHINGFILTER_HPP_
#define GAUSSIANSMOOTHINGFILTER_HPP_

#include "ProcessObject.hpp"
#include "ExecutionDevice.hpp"
#include "Image.hpp"

namespace fast {

class GaussianSmoothingFilter : public ProcessObject {
    FAST_OBJECT(GaussianSmoothingFilter)
    public:
        void setInput(ImageData::pointer input);
        void setDevice(ExecutionDevice::pointer device);
        void setMaskSize(unsigned char maskSize);
        void setStandardDeviation(float stdDev);
        ImageData::pointer getOutput();
        ~GaussianSmoothingFilter();
    private:
        GaussianSmoothingFilter();
        void execute();
        void createMask(Image::pointer input);

        ImageData::pointer mInput;
        WeakPointer<ImageData> mOutput;
        ImageData::pointer mTempOutput;
        ExecutionDevice::pointer mDevice;
        unsigned char mMaskSize;
        float mStdDev;

        cl::Buffer mCLMask;
        float * mMask;
        float mRecreateMask;

};

} // end namespace fast




#endif /* GAUSSIANSMOOTHINGFILTER_HPP_ */