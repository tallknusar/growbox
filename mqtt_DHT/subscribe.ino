void subscribeToTopics(){
  client.subscribe("growbox/temperature/set");
    client.subscribe("growbox/temperature/get");
    client.subscribe("growbox/temperature/getReq");
    client.subscribe("growbox/pid/p/set");
    client.subscribe("growbox/pid/i/set");
    client.subscribe("growbox/pid/d/set");
    client.subscribe("growbox/pid/p/getReq");
    client.subscribe("growbox/pid/i/getReq");
    client.subscribe("growbox/pid/d/getReq");
    client.subscribe("growbox/save");
    client.subscribe("growbox/time/getReq");
    client.subscribe("growbox/time/hour/on/set");
    client.subscribe("growbox/time/hour/off/set");
    client.subscribe("growbox/time/min/off/set");
    client.subscribe("growbox/time/min/on/set");
    client.subscribe("growbox/time/hour/off/getReq");
    client.subscribe("growbox/time/hour/on/getReq");
    client.subscribe("growbox/time/min/off/getReq");
    client.subscribe("growbox/time/min/on/getReq");
}

