/**
 * @cite Proxy Pattern states that when a resource is expensive, hard to construct or require logging etc. then an interface is created over the resource in order to control access to it, which posses the same API as the resource itself.
 * Aims at granular control of the resources as the resources are closely monitored through the proxy class.
 *
 * @brief Proxy Pattern can be exemplified by CloudServices class that runs all the cloud services which are expensive.
 * How do we postpone building the resource till the last moment until we actually need it as its construction is also expensive?
 * What happens when we need to monitor the each service call ?
 */

#include <iostream>

/**
 * @brief Abstraction for Cloud Services.
 */
class AbstractCloudService
{
public:
    virtual void call_service() = 0;
};

/**
 * @brief Cloud Service that builds the service in the contructor and not Lazily(i.e. only when needed).
 * @brief It can't provide any monitoring messages without breaking the OCP principle.
 */
class CloudService : public AbstractCloudService
{
public:
    // ! Building the object in the contructor rather than when required.
    CloudService()
    {
        std::cout << "Cloud Service is being built !!!\n";
    }
    // ! No Monitoring Messages for the call to cloud service.
    void call_service() override
    {
        std::cout << "Service Called !!!\n";
    }
};

/**
 * @brief Lazy Cloud Service only initializes the CloudService only when it is actually required.
 * @brief It also provides Monitroing Messages over the calls to the service.
 * 
 * Acts as a virtual proxy as it doesn't have the object that it is proxying.
 */
class LazyCloudService : public AbstractCloudService
{
    CloudService *cs{nullptr};

public:
    void call_service() override
    {
        std::cout << "Monitoring Message Begin ...\n\t";
        if (!cs)
        {
            // * Initializing only when needed.
            cs = new CloudService();
            std::cout << "\t";
        }

        // * Mointoring Messages wrapping the service call.
        
        cs->call_service();
        
        std::cout << "Montoring Message End ...";
    }
};

int main()
{
    CloudService cs;
    cs.call_service();

    std::cout << "\n";

    // * The driver code remains exactly the same just the typename changes.
    LazyCloudService lcs;
    lcs.call_service();

    return 0;
}