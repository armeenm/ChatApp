#include <cstdlib>
#include <fmt/core.h>
#include <sleepy_discord/sleepy_discord.h>

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
  using SleepyDiscord::DiscordClient::DiscordClient;
  void onMessage(SleepyDiscord::Message message) override {
    if (message.startsWith("$hello"))
      sendMessage(message.channelID, "Hello " + message.author.username);
  }
};

int main() {
  try {
    auto const token = std::getenv("DISCORD_BOT_TOKEN");
    MyClientClass client(token, SleepyDiscord::USER_CONTROLED_THREADS);
    client.run();
  } catch (std::exception const& e) {
    fmt::print("Caught exception: {}\n", e.what());
  }
}
