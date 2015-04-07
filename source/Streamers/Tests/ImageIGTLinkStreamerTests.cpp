#include "catch.hpp"
#include "ImageIGTLinkStreamer.hpp"
#include "DummyIGTLImageServer.hpp"
#include "ImageRenderer.hpp"
#include "SimpleWindow.hpp"

using namespace fast;

TEST_CASE("Stream 2D images using ImageIGTLinkStreamer", "[ImageIGTLinkStreamer][fast][IGTLink]") {

    ImageFileStreamer::pointer fileStreamer = ImageFileStreamer::New();
    fileStreamer->setFilenameFormat(std::string(FAST_TEST_DATA_DIR) + "US-2Dt/US-2Dt_#.mhd");
    fileStreamer->setStreamingMode(STREAMING_MODE_PROCESS_ALL_FRAMES);
    DummyIGTLImageServer server;
    server.setImageStreamer(fileStreamer);
    server.setPort(18944);
    server.start();

    ImageIGTLinkStreamer::pointer streamer = ImageIGTLinkStreamer::New();
    streamer->setConnectionAddress("localhost");
    streamer->setConnectionPort(18944);

    ImageRenderer::pointer renderer = ImageRenderer::New();
    renderer->addInputConnection(streamer->getOutputPort());
    SimpleWindow::pointer window = SimpleWindow::New();
    window->addRenderer(renderer);
    window->setTimeout(5000);
    window->start();
}
